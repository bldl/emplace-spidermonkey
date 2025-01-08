// |reftest| shell-option(--enable-symbols-as-weakmap-keys) skip-if(release_or_beta||!xulRuntime.shell) -- symbols-as-weakmap-keys is not released yet, requires shell-options
// Copyright (C) 2022 Igalia, S.L. All rights reserved.
// Copyright (C) 2025 Jonas Haukenes. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.
/*---
esid: proposal-upsert
description: >
  Adds a value with a Symbol key if key is not already in the map.
info: |
  WeakMap.prototype.getOrInsertComputed ( _key_, callbackfn )

  ...
  8. Let p be the Record { [[Key]]: key, [[Value]]: value }.
  9. Append p to M.[[WeakMapData]].
features: [Symbol, WeakMap, symbols-as-weakmap-keys]
---*/

var map = new WeakMap();
var foo = Symbol('a description');
var bar = Symbol('a description');

map.getOrInsertComputed(foo, () => 1);
map.getOrInsertComputed(bar, () => 2);
map.getOrInsertComputed(Symbol.hasInstance, () => 3);

assert(map.has(bar), 'Regular symbol as key');
assert.sameValue(map.get(foo), 1, "Symbols with the same description don't overwrite each other");
assert(map.has(Symbol.hasInstance), 'Well-known symbol as key');

assert.sameValue(map.get(bar), 2);
assert.sameValue(map.get(Symbol.hasInstance), 3);

reportCompare(0, 0);
