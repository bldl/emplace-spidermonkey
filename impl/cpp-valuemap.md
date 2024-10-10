# CPP without has-set-get

in `MapObject.h`

```cpp

    //public
    [[nodiscard]] static bool emplace(JSContext* cx, unsigned argc, Value* vp);

```

in `MapObject.cpp`

```cpp

    //hook
    JS_FN("emplace", MapObject::emplace, 2, 0),

    //def
    bool MapObject::emplace(JSContext* cx, unsigned argc, Value* vp) {
        // Step 1: Access the arguments
        CallArgs args = CallArgsFromVp(argc, vp);
        
        // Ensure we have exactly two arguments: key and value
        if (args.length() != 2) {
            JS_ReportErrorASCII(cx, "Map.prototype.emplace requires two arguments: key and value");
            return false;
        }

        // Step 2: Extract the map (this object), key, and value
        RootedObject obj(cx, &args.thisv().toObject()); // 'this' as the Map object
        RootedValue key(cx, args[0]); // first argument is the key
        RootedValue value(cx, args[1]); // second argument is the value

        // Step 3: Extract the underlying map data (table)
        MapObject* mapObject = &obj->as<MapObject>();
        ValueMap* table = mapObject->getTableUnchecked();
        if (!table) {
            // Return false if we can't access the table
            return false;
        }

        // Step 4: Prepare the hashable key (common to both get/set operations)
        Rooted<HashableValue> hashKey(cx);
        if (!hashKey.setValue(cx, key)) {
            return false;
        }

        // Step 5: Perform a single lookup for the key
        const ValueMap::Entry* entry = table->get(hashKey);
        if (entry) {
            // Key exists, return the existing value
            args.rval().set(entry->value);
            return true;
        }

        // Step 6: Key doesn't exist, insert the new key-value pair
        bool needsPostBarriers = mapObject->isTenured();
        if (needsPostBarriers) {
            // Insert using post barriers, cast obj to MapObject*
            if (!PostWriteBarrier(mapObject, hashKey.get()) || !table->put(hashKey.get(), value)) {
                ReportOutOfMemory(cx);
                return false;
            }
        } else {
            // Insert without post barriers (PreBarrieredTable)
            auto* preBarrieredTable = reinterpret_cast<PreBarrieredTable*>(table);
            if (!preBarrieredTable->put(hashKey.get(), value.get())) {
                ReportOutOfMemory(cx);
                return false;
            }
        }

        // Step 7: Set the return value to the newly inserted value
        args.rval().set(value);
        return true;
    }

```