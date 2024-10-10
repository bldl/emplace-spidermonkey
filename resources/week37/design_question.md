Callback function should not take `key` as an argument:
  1. Simplicity. Not taking the key makes the function easier to use and write.
  2. Unnecessary to take the key if it is not going to be used. The callbacks behaviour may not depend on the key.
  3. Cleaner interface. Not taking the `key` results in cleaner and more concise code.
  4. Less error-prone. By keeping it simpler, we also reduce the risk of the callback being incorrectly used.
  5. Redundancy. The key might be available through the outer scope.
  6. Familiar. Looks more like the setdefault in python.

Callback function should take `key` as an argument:
  1. Predictability. The behaviour becomes more predictable. 
  2. Flexibility. You might need the key to calculate the default value. This offers more flexibility as the function might need to behave differently based on the key.
  3. Immutability. Passing the `key` directly into the callback, would avoid potential bugs where the `key` might have changed.
  4. Consistency. If `key` is passed as an argument, you are ensured that the callback has access to it.
  5. Parallelism. Avoiding potential race conditions if the callbacks are ran asynchronously. 
