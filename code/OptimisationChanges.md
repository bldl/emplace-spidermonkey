# Optimised version using HashTable getOrAdd

Since I wasn't a 100% sure of how to do it, I tried to follow what the other functions did.
Specifically, has and set.

I made changes to the following files and line numbers:

* js/src/builtin/MapObject.cpp, lines: 520, 734-768, 1020-1026, 1028-1033
* js/src/builtin/MapObject.h, lines: 188-189, 220-222, 244-245
* js/src/ds/OrderedHashTable.h, lines: 990-993

I think most should be fine, as I followed the implementations of get and set.
As the implementation passes all the tests we have written, which can be found in the test262 folder in this repo.

But on line `759` in `MapObject.cpp`, I ended up using `auto` for the type of the const as I wasn't sure what the correct one was.
If this needs to be changed, could you help me figure out what the correct type should be?
