# The `Map.prototype.emplace` proposal

## Table of Contents
- [intro](README.md)
- [The `Map.prototype.emplace` proposal](tutorial/initial-proposal.md)
- [Installing mozilla unified](tutorial/installing-mozilla-unified.md)
- [Get to know the tools](tutorial/tools.md)
- [How to Read the ECMA-262 Language Specification](tutorial/reading-Ecma262-specs.md)
- [implementing the proposal](tutorial/implementation.md)

   
__What is it?__
Map.prototype.emplace is a new method for JavaScript's Map-object. The operation simplifies the process of inserting or updating key-value pairs in the Map. The function simply checks for existence of a key to either insert or update new key-value pairs. 

__How does it work?__ 
The "emplace" operation takes two arguments: a key and a handler object. The handler contains two properties:
* update: Function to modify value of a key if the key is already existing in the Map.
* insert: Function that generates a default-value to be set to the belonging value of the checked key. 
   
   
__The function follow these steps:__

1. The Map is checked for the key passed as argument. If the key is found:
    * It checks the handler for "update" function. If found this is used to update the value belonging to the key to then return it 
2. If it is not found, the insert function from the handler is used to generate a new value, assign this to the passed key and then return the new value. 
3. Either way, the belonging value will be returned. 

__What is the motivation?__ Adding and updating values of a Map are tasks that developers often perform in conjunction. There are currently no Map prototype methods for either of those two things, let alone a method that does both. The workarounds involve multiple lookups and developer inconvenience while avoiding encouraging code that is surprising or is potentially error prone.

<details>
<summary>
Either update or insert for a specific key
</summary>

Before:
```javascript
// two lookups
old = map.get(key);
if (!old) {
    map.set(key, value);
} else {
    map.set(key, updated);
}
```

Using emplace:
```javascript
map.emplace(key, {
    update: () => updated,
    insert: () => value
});
```
</details>
<details>
<summary>
Just insert if missing:
</summary>

Before:
```javascript
// two lookups
if (!map1.has(key)) {
    map1.set(key, value);
}
```

Using emplace:

```javascript
map.emplace(key, {
    insert: () => value
});
```
</details>
<details>
<summary>
Just update if present:
</summary>

Before:
```javascript
// three lookups
if (map.has(key)) {
    old = map.get(key);
    updated = old.doThing();
    map.set(key, updated);
}
```

Using emplace:

```javascript
if (map.has(key)) {
    map.emplace(key, {
    update: (old) => old.doThing()
    });
}
```
</details>