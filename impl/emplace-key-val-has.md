
in `MapObject.h`
```cpp
    //moved from private to public
    [[nodiscard]] static bool has(JSContext* cx, unsigned argc, Value* vp);
```

in `SelfHosting.cpp`
```cpp
    JS_FN("std_Map_entries", MapObject::entries, 0, 0),
    JS_FN("std_Map_get", MapObject::get, 1, 0),
    JS_INLINABLE_FN("std_Map_has", MapObject::has, 1, 0, MapHas), // has, needs to be defined before set
    JS_FN("std_Map_set", MapObject::set, 2, 0),
```

Implementation in `Map.js`
```js
    function MapEmplace(key, value) {
    var M = this;

    // perform internalslot, verify the given object is a map
    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
        return callFunction(      
            CallMapMethodIfWrapped, 
            this,
            key,
            value,             
            "MapEmplace"
        );
    }

    if (callContentFunction(std_Map_has, M, key)) {
        return callFunction(std_Map_get, M, key);
    }

    callContentFunction(std_Map_set, M, key, value);
    return value;
    }
```