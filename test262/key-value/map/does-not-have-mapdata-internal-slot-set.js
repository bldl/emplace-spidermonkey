// Copyright (C) 2024 Sune Eriksson Lianes. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.
/*---
esid: pending
description: >
    Throws a TypeError if `this` is a Set Object
info: |
    Map.getOrInsert ( key , value )

    ...
    2. Perform ? RequireInternalSLot(M, [[MapData]])
    ...
features: [Set]
---*/

var map = new Map();

assert.throws(TypeError, function () {
    map.getOrInsert.call(new Set(), 1, 1);
});

assert.throws(TypeError, function () {
    map.getOrInsert.call(new Set(), 1, 1);
});

reportCompare(0, 0);