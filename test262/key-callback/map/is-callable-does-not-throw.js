// Copyright (C) 2015 the V8 project authors. All rights reserved.
// Copyright (C) 2024 Mathias Ness. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.
/*---
esid: proposal-upsert
description: >
  Does not throw if `callbackfn` is callable.
info: |
  Map.prototype.getOrInsertComputed ( key , callbackfn )

   ...
  3. If IsCallable(callbackfn) is false, throw a TypeError exception.
  ...

  features: [arrow-function]
---*/

var m = new Map();

assert.doesNotThrow(function () {
    m.getOrInsertComputed.call(m, 1, function() {});
});

assert.doesNotThrow(function () {
    m.getOrInsertComputed.call(m, 2, () => {});
});

assert.doesNotThrow(function () {
    m.getOrInsertComputed.call(m, 3, (function() {}).bind(m));
});

assert.doesNotThrow(function () {
    m.getOrInsertComputed.call(m, 4, new Function());
});

assert.doesNotThrow(function () {
    m.getOrInsertComputed.call(m, 5, { 
        call: function() {} 
    });
});

reportCompare(0, 0);
