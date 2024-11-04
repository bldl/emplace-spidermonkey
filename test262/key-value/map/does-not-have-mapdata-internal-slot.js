// Copyright (C) 2015 the V8 project authors. All rights reserved.
// Copyright (C) 2024 Sune Eriksson Lianes. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.
/*---
esid: pending
description: >
    Throws a TypeError if `this` object does not have a [[MapData]] internal slot.
info: |
    Map.getOrInsert ( key , value )

    ...
    2. Perform ? RequireInternalSLot(M, [[MapData]])
    ...
---*/

var map = new Map();

assert.throws(TypeError, function () {
    Map.prototype.getOrInsert.call([], 1, 1);
});

assert.throws(TypeError, function () {
    map.getOrInsert.call([], 1, 1);
});

assert.throws(TypeError, function () {
    Map.prototype.getOrInsert.call({}, 1, 1);
});

assert.throws(TypeError, function () {
    map.getOrInsert.call({}, 1, 1);
});

reportCompare(0, 0);