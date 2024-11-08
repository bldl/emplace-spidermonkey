// Copyright (C) 2015 the V8 project authors. All rights reserved.
// Copyright (C) 2024 Sune Eriksson Lianes, Mathias Ness. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.
/*---
esid: proposal-upsert
description: >
    Throws a TypeError if `this` object does not have a [[MapData]] internal slot.
info: |
    Map.getOrInsertComputed ( key , callbackfn )

    ...
    2. Perform ? RequireInternalSLot(M, [[MapData]])
    ...

    features: [arrow-function]
---*/

var map = new Map();

assert.throws(TypeError, function () {
    Map.prototype.getOrInsertComputed.call([], 1, () => 1);
});

assert.throws(TypeError, function () {
    map.getOrInsertComputed.call([], 1, () => 1);
});

assert.throws(TypeError, function () {
    Map.prototype.getOrInsertComputed.call({}, 1, () => 1);
});

assert.throws(TypeError, function () {
    map.getOrInsertComputed.call({}, 1, () => 1);
});

reportCompare(0, 0);