

let map = new Map([['key1', undefined]]);

// Emplace a new key with undefined value
map.emplace('key2', undefined);

assert.sameValue(map.get('key1'), undefined, "'key1' should still map to undefined.");
assert.sameValue(map.get('key2'), undefined, "'key2' should map to undefined.");
assert.sameValue(map.size, 2, "Map size should be 2.");

reportCompare(0, 0);