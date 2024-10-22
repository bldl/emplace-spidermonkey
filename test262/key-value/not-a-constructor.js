
assert.sameValue(isConstructor(Map.prototype.getOrInsert), false, 'isConstructor(Map.prototype.getOrInsert) must return false');

assert.throws(TypeError, () => {
    let m = new Map(); new m.getOrInsert();
});

reportCompare(0, 0);