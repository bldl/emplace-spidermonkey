Map.prototype.emplace = function (key, defaultValue) {
    if (this.has(key)) {
      return this.get(key);
    }
    this.set(key, defaultValue);
    return this.get(key);
  };
  
  class DefaultMap extends Map {
    constructor(callback) {
      super();
      this.callback = callback;
    }
  
    get(key) {
      if (this.has(key)) {
        return super.get(key);
      }
      
      // Verify that callback is callable
      if (typeof this.callback !== 'function') {
        throw new TypeError('Callback is not a function');
      }
      
      var defaultValue = this.callback();
      this.set(key, defaultValue);
      return defaultValue;
    }
}

// Test 1: Verify DefaultMap works with a valid callback
const map1 = new DefaultMap(() => "default value");

console.assert(map1.get("nonexistent") === "default value", "Test 1 Failed");
console.assert(map1.get("nonexistent") === "default value", "Test 1 Failed (after insertion)");

// Test 2: Verify that the key is added after calling get
console.assert(map1.has("nonexistent"), "Test 2 Failed");

// Test 3: Verify that emplace works as expected
const map3 = new Map();
map3.emplace("key1", "value1");
console.assert(map3.get("key1") === "value1", "Test 4 Failed");

map3.emplace("key1", "newValue");
console.assert(map3.get("key1") === "value1", "Test 4 Failed (no overwrite)");

// Test 4: Verify DefaultMap works with emplace
const map4 = new DefaultMap(() => "default value");
map4.emplace("key2", "default value");
console.assert(map4.get("key2") === "default value", "Test 5 Failed");
