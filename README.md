# emplace-spidermonkey

## `emplace(key, handler)`

## `emplace(key, value)`
The `emplace` function checks if a given key exists in a map. If the key is present, it returns the associated value, similar to the behavior of `get()`. If the key does not exist, it inserts the key-value pair into the map and returns the map itself. This function is useful when you want to retrieve a value if it exists or insert a new key-value pair in one operation, reducing the need for separate get and set calls.

```javascript
function MapEmplace(key, value) {
    //1
    var M = this;
    
    //2
    if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
      return callFunction(      
        CallMapMethodIfWrapped, 
        this,
        key,
        value,             
        "MapEmplaceKV"
      );
    }
    
    //3
    var entries = callFunction(std_Map_entries, M);
  
    for (var e of allowContentIter(entries)) {
      var eKey = e[0];   
      var eValue = e[1];
  
      if (SameValueZero(eKey, key)) {
        return callContentFunction(std_Map_get, M, key);
      }
    }
    //4
    callContentFunction(std_Map_set, M, key, value);
    
    //5
    return M;
  }
```

## `emplace(key, cb)`
