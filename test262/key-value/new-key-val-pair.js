

let map = new Map();

// Emplace a new key-value pair
map.emplace('key', 'val');

assert.sameValue(map.get('key'), 'val', "Key 'key' should be set to 'val'.");
assert.sameValue(map.size, 1, "Map size should be 1 after inserting 'key'.");

reportCompare(0, 0);