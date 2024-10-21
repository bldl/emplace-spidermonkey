


let map = new Map();

map.emplace(123, 'numberKey');
map.emplace('stringKey', 456);
map.emplace(true, false);

assert.sameValue(map.get(123), 'numberKey', "'123' should be mapped to 'numberKey'.");
assert.sameValue(map.get('stringKey'), 456, "'stringKey' should be mapped to '456'.");
assert.sameValue(map.get(true), false, "'true' should be mapped to 'false'.");

reportCompare(0, 0);