# Tutorial

## The `Map.prototype.emplace` proposal

__What is it?__
Map.prototype.emplace is a new method for JavaScript's Map-object. The operation simplifies the process of inserting or updating key-value pairs in the Map. The function simply checks for existence of a key to either insert or update new key-value pairs. 

__How does it work?__ 
The "emplace" operation takes two arguments: a key and a handler object. The handler contains two properties:
* update: Function to modify value of a key if the key is already existing in the Map.
* insert: Function that generates a default-value to be set to the belonging value of the checked key. 


__The function follow these steps:__

1. The Map is checked for the key passed as argument. If the key is found:
    * It checks the handler for "update" function. If found this is used to update the value belonging to the key to then return it 
2. If it is not found, the insert function from the handler is used to generate a new value, assign this to the passed key and then return the new value. 
3. Either way, the belonging value will be returned. 

__What is the motivation?__ Adding and updating values of a Map are tasks that developers often perform in conjunction. There are currently no Map prototype methods for either of those two things, let alone a method that does both. The workarounds involve multiple lookups and developer inconvenience while avoiding encouraging code that is surprising or is potentially error prone.

## Installing mozilla unified

Installing Mozilla Unified and other tools.
Specific instructions for different OS by link.
hg/mercurial or git.
Building and running the engine.
Changing the code and rebuild.


## Tools
how to read specs, how to use searchfox

## implementation
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

self hosted code is different

```cpp
// Standard builtins used by self-hosting.
    JS_FN("std_Map_entries", MapObject::entries, 0, 0),
    JS_FN("std_Map_get", MapObject::get, 1, 0),
    JS_FN("std_Map_set", MapObject::set, 2, 0),
```

use std_Map_entries to get the list of entry records

```
3. Let entries be the List that is M.[[MapData]].
```

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

step 4 iterating through the entries

```
4. For each Record { [[Key]], [[Value]] } e that is an element of entries, do
```

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

verify that the given key is in the map if update
perform abstract operation SameValueZero

```
4a. If e.[[Key]] is not empty and SameValueZero(e.[[Key]], key) is true, then
```

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
