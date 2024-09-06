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
        "MapEmplace"
      );
    }
    
    // Step 3.
    var entries = callFunction(std_Map_entries, M);
  
    for (var e of allowContentIter(entries)) {
      var eKey = e[0];   
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