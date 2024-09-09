function MapEmplace(key, callbackfn) {
  //Step 1
  var M = this;

  //Step 2
  if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
    return callFunction(      
      CallMapMethodIfWrapped, 
      this,
      key,
      callbackfn,             
      "MapEmplace"
    );
  }

  //Step 3
  if (!IsCallable(callbackfn)) {
    ThrowTypeError(JSMSG_NOT_FUNCTION, DecompileArg(1, callbackfn));
  }

  //Step 4
  var entries = callFunction(std_Map_entries, M);
  
  for (var e of allowContentIter(entries)) {
    var eKey = e[0];   
    
    if (SameValueZero(eKey, key)) {
      return callContentFunction(std_Map_get, M, key);
    }
  }

  //Step 5
  var inserted = callContentFunction(callbackfn, key);

  //Step 6
  callContentFunction(std_Map_set, M, key, inserted);

  //Step 7
  return inserted;
}
