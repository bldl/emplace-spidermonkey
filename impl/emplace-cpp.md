
in `MapObject.h`

```cpp
    //public
    [[nodiscard]] static bool emplaceCPP(JSContext* cx, unsigned argc, Value* vp);
```

in `MapObject.cpp`
```cpp
    //hook
    JS_FN("emplace", MapObject::emplace, 2, 0),

    //def
    bool MapObject::emplace(JSContext* cx, unsigned argc, Value* vp) {
    // Ensure we have the right number of arguments (key and value)
    CallArgs args = CallArgsFromVp(argc, vp);
    if (args.length() < 2) {
        JS_ReportErrorASCII(cx, "Map.prototype.emplace requires two arguments: key and value");
        return false;
    }

    // Extract the object, key, and value
    RootedObject obj(cx, &args.thisv().toObject());
    RootedValue key(cx, args.get(0));
    RootedValue value(cx, args.get(1));

    // Declare a mutable handle for the return value
    RootedValue rval(cx);

    // Check if the key exists using has
    bool found = false;
    if (!MapObject::has(cx, obj, key, &found)) {
        return false;
    }

    // If the key exists, return the value
    if (found) {
        if (!MapObject::get(cx, obj, key, &rval)) {
            return false;
        }
        args.rval().set(rval);
        return true;
    }

    // If the key does not exist, insert the key-value pair
    if (!MapObject::set(cx, obj, key, value)) {
        return false;
    }

    // Return the inserted value
    args.rval().set(value);
    return true;
}
```