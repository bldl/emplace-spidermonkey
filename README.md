# emplace-spidermonkey

## `emplace(key, handler)`

The `emplace(key, handler)` function checks if a given key exists in a map. If the key is present, it updates the value based on the `handler["update"]` function, and returns the associated value. If the key does not exist, it will get a new value from the `handler["update"]` function, and insert the key-value pair into the map and return the value. This function is useful when you want to have a lot of freedom to manipulate, retrieve a value if it exists or insert a new key-value pair in one operation, reducing the need for separate get and set calls.

```js
function MapEmplace(key, handler) {
  // Step 1.
  var M = this;

  // Step 2.
  if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(
      CallMapMethodIfWrapped,
      this,
      key,
      handler,
      "MapEmplace"
    );
  }
  // Step 3.
  var entries = callFunction(std_Map_entries, M);
  // Step 4.
  for (var e of allowContentIter(entries)) {
    var Key = e[0];
    var Value = e[1];
    // Step 4.a.
    if (SameValueZero(Key, key)) {
      // Step 4.a.i.
      if (callFunction(Object_hasOwnProperty, handler, 'update')) {
        // Step 4.a.i.1.
        var updateFN = handler['update'];
        // Step 4.a.i.2.
        var updated = callContentFunction(updateFN, M, Value, key);
        // Step 4.a.i.3.
        callFunction(std_Map_set, M, key, updated);
      }
      // Step 4.a.ii.
      return callFunction(std_Map_get, M, key);
    }
  }
  // Step 5.
  var insertFN = handler['insert'];
  // Step 6.
  var inserted = callContentFunction(insertFN, key, M);
  // Step 7.
  callFunction(std_Map_set, M, key, inserted);
  // Step 8.
  return callFunction(std_Map_get, M, key);
}
```

## `emplace(key, value)`

The `emplace(key, value)` function checks if a given key exists in a map. If the key is present, it returns the associated value, similar to the behavior of `get()`. If the key does not exist, it inserts the key-value pair into the map and returns the default value. This function is useful when you want to retrieve a value if it exists or insert a new key-value pair in one operation, reducing the need for separate get and set calls.

```javascript
function MapEmplace(key, value) {
    // Step 1.
    var M = this;
    
    // Step 2.
    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
      return callFunction(      
        CallMapMethodIfWrapped, 
        this,
        key,
        value,             
        "MapEmplaceKV"
      );
    }
    
    // Step 3.
    var entries = callFunction(std_Map_entries, M);
  
    for (var e of allowContentIter(entries)) {
      var eKey = e[0];   
      var eValue = e[1];
      // Step 3.a. 
      if (SameValueZero(eKey, key)) {
        return callContentFunction(std_Map_get, M, key);
      }
    }
    // Step 4.
    callContentFunction(std_Map_set, M, key, value);
    
    // Step 5.
    return callContentFunction(std_Map_get, M, key);
  }
```

## `emplace(key, cb)`
