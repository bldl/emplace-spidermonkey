

let map = new Map([['key', 'val']]);

// Emplace the same key with a new value (should not overwrite)
let result = map.emplace('key', 'newValue');

assert.sameValue(result, 'val', "Emplace should return the existing value 'val'.");
assert.sameValue(map.get('key'), 'val', "'key' should remain 'val'.");
assert.sameValue(map.size, 1, "Map size should still be 1.");

reportCompare(0, 0);