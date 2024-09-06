function MapEmplaceKV(key, value) {
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