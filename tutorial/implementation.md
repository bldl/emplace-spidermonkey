# Implementing the proposal

## Table of Contents
[intro](README.md)
[The `Map.prototype.emplace` proposal](tutorial/initial-proposal.md)
[Installing mozilla unified](tutorial/installing-mozilla-unified.md)
[Get to know the tools](tutorial/tools.md)
[How to Read the ECMA-262 Language Specification](tutorial/reading-Ecma262-specs.md)
[implementing the proposal](tutorial/implementation.md)


### creating a function

create a hook in `MapObject.cpp`

`JS_SELF_HOSTED_FN("emplace", "MapEmplace", 2,0),`

in `Map.js`

```javascript
function MapEmplace(key, handler) {
    return 42
}
```

build to test

### implement the first line

```
1. Let M be the this value.
```

```javascript
function MapEmplace(key, handler) {
    var M = this;
}
```

### moving on
explain the purpose of performing internal slot

borrow from ForEach

```
2. Perform ? RequireInternalSlot(M, [[MapData]]).
```

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }
}
```

</details>

**`callfunction` vs `callcontentfunction`?**

Why do we need to use `callFunction` and `callContentFunction`?
In self-hosted JavaScript code, directly calling methods like map.get() is not allowed because content (external scripts) 
could modify built-in objects like Map. This could lead to unexpected behavior if a method, like get, has been changed by 
content. This scenario is called monkeyPatching. 

`callFunction` is an optimized version of `callContentfunction`, however it has a tradeoff. `callContentFunction` is 
safer when there is a potential risk of the object or method being altered it's `callFunction` is not guaranteed to work.
**general rule**
Use `callContentFunction` when interfering with the `this` object. In the case of this tutorial, `M`.

Read more [here](https://udn.realityripple.com/docs/Mozilla/Projects/SpiderMonkey/Internals/self-hosting)

self hosted code is different
    - We can use other methods written in selfhosted code
    - We can use methods methods specified in selfHosting.cpp, which are made available to selfhosted code.

```cpp
// Standard builtins used by self-hosting.
// Code snippet from SelfHosting.cpp
    JS_FN("std_Map_entries", MapObject::entries, 0, 0),
    JS_FN("std_Map_get", MapObject::get, 1, 0),
    JS_FN("std_Map_set", MapObject::set, 2, 0),
```

use std_Map_entries to get the list of entry records

```
3. Let entries be the List that is M.[[MapData]].
```

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);
}
```

</details>


step 4 iterating through the entries

```
4. For each Record { [[Key]], [[Value]] } e that is an element of entries, do
```
<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    //...
    }
}
```

</details>


verify that the given key is in the map if update
perform abstract operation SameValueZero

```
4a. If e.[[Key]] is not empty and SameValueZero(e.[[Key]], key) is true, then
```
<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        //...
    }
    }
}
```

</details>


```
4ai. If HasProperty(handler, "update") is true, then
```
In Javascript almost "everything" is an object. All values except primitives are objects. This means we can use selfhosted
Object methods on almost "everything".

```cpp
// Code snippet from Object.cpp
static const JSFunctionSpec object_methods[] = {
    //...
    JS_SELF_HOSTED_FN("toLocaleString", "Object_toLocaleString", 0, 0),
    JS_SELF_HOSTED_FN("valueOf", "Object_valueOf", 0, 0),
    JS_SELF_HOSTED_FN("hasOwnProperty", "Object_hasOwnProperty", 1, 0),
    //...
    JS_FS_END,
};
```

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        //...
        }
    }
    }
}
```

</details>

```
4ai1. Let updateFn be ? Get(handler, "update").
```

get the update handler if its specified.

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        var updateFN = handler['update'];
        //...
        }
    }
    }
}
```

</details>

```
4ai2. Let updated be ? Call(updateFn, handler, « e.[[Value]], key, M »).
```

Use `callFunction` to call updateFN, store it as `var updated`

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        var updateFN = handler['update'];
        var updated = callFunction(updateFN, M, Value, key);
        //...
        }
    }
    }
}
```

</details>

```
4ai3. Set e.[[Value]] to updated.
```

Perform a set operation on the Map to update it.

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        var updateFN = handler['update'];
        var updated = callFunction(updateFN, M, Value, key);
        callContentFunction(std_Map_set, M, key, updated);
        }
    }
    }
}
```

</details>

```
4aii. Return e.[[Value]].
```

Now that we have updated the map, the updated value should be returned.

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        var updateFN = handler['update'];
        var updated = callFunction(updateFN, M, Value, key);
        callContentFunction(std_Map_set, M, key, updated);
        }

        return updated;
    }
    }
}
```

</details>

```
5. Let insertFn be ? Get(handler, "insert").
6. Let inserted be ? Call(insertFn, handler, « e.[[Value]], key, M »).
7. Set e.[[Value]] to inserted.
8. Return e.[[Value]].
```

With the knowledge from implementing update, use similar techniques to implement insert. 

<details>
<summary>Solution</summary>

```javascript
function MapEmplace(key, handler) {
    var M = this;

    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
        CallMapMethodIfWrapped,
        this,
        key,
        handler,
        "MapEmplace"
    );
    }

    var entries = callFunction(std_Map_entries, M);

    for (var e of allowContentIter(entries)) {
    var eKey = e[0];
    var eValue = e[1];
    
    if (SameValueZero(key, eKey)) {
        if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        var updateFN = handler['update'];
        var updated = callFunction(updateFN, M, Value, key);
        callContentFunction(std_Map_set, M, key, updated);
        }

        return updated;
    }
    }

    var insertFN = handler['insert'];
    var inserted = callFunction(insertFN, key, M);
    callContentFunction(std_Map_set, M, key, inserted);

    return inserted;
}
```

</details>