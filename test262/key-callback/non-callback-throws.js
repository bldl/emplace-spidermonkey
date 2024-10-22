
const m = new Map();

assert.throws(TypeError, function() {
    m.getOrInsertWithCallback(1, 0)
}, 'Should throw a TypeError when the callback is not a function');

assert.throws(TypeError, function() {
    m.getOrInsertWithCallback(1, "string")
}, 'Should throw a TypeError when the callback is not a function');

assert.throws(TypeError, function() {
    m.getOrInsertWithCallback(1, 'c')
}, 'Should throw a TypeError when the callback is not a function');

assert.throws(TypeError, function() {
    m.getOrInsertWithCallback(1, true)
}, 'Should throw a TypeError when the callback is not a function');

reportCompare(0, 0);