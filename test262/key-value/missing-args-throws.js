

let map = new Map();

assert.throws(Error, function() {
  map.emplace();
}, 'Emplace should throw a TypeError when no arguments are provided.');

assert.throws(Error, function() {
  map.emplace('keyOnly');
}, 'Emplace should throw a TypeError when only the key is provided.');

assert.throws(Error, function() {
    map.emplace('key', 'val', 'extra');
  }, 'Emplace should throw a TypeError when more than two arguments are provided.');

reportCompare(0, 0);