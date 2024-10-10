# Tutorial

General info here maybe?

**TODO testing is introduced in the end of the tutorial, but there are other ways to test implementation, writing scripts**

**TODO? explain the process of an Ecmascript proposal, ex. phases2 -> 2.7 etc**

<details>
   <summary><h2>The `Map.prototype.emplace` proposal</h2></summary>

   **What is it?**
   Map.prototype.emplace is a new method for JavaScript's Map-object. The operation simplifies the process of inserting or updating key-value pairs in the Map. The function simply checks for existence of a key to either insert or update new key-value pairs.

   **How does it work?**
   The "emplace" operation takes two arguments: a key and a handler object. The handler contains two properties:

* update: Function to modify value of a key if the key is already existing in the Map.
* insert: Function that generates a default-value to be set to the belonging value of the checked key.

   **The function follow these steps:**

   1. The Map is checked for the key passed as argument. If the key is found:
       * It checks the handler for "update" function. If found this is used to update the value belonging to the key to then return it
   2. If it is not found, the insert function from the handler is used to generate a new value, assign this to the passed key and then return the new value.
   3. Either way, the belonging value will be returned.

   **What is the motivation?** Adding and updating values of a Map are tasks that developers often perform in conjunction. There are currently no Map prototype methods for either of those two things, let alone a method that does both. The workarounds involve multiple lookups and developer inconvenience while avoiding encouraging code that is surprising or is potentially error prone.

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

</details>

<details>
   <summary><h2>Installing mozilla unified</h2></summary>

   In this section you will learn how to download the Mozilla environment based on your operating system. It will also feature setting up SpiderMonkey for development and introduce main tools which are used during development.

### 1. Installation of SpiderMonkey and required tools

  We will start by installing SpiderMonkey and all required tools.

  Before you start installing, we advice you to open a terminal and navigate to the desired location of the `mozilla_unified` folder.

  The installation process depends on your operating system, therefore you can click on the link under that matches yours.

* [Build Mozilla Firefox on Linux](https://firefox-source-docs.mozilla.org/setup/linux_build.html)
* [Build Mozilla Firefox on Mac](https://firefox-source-docs.mozilla.org/setup/macos_build.html)
* [Build Mozilla Firefox on Windows](https://firefox-source-docs.mozilla.org/setup/windows_build.html)

  During the installation, you will be asked which version of Firefox we want to build as a standard. In this tutorial we will choose `5: SpiderMonkey JavaScript engine`, which will allow for faster builds during development

  When asked if you want to use the Configuration Wizard, say no(?)

  **TODO check the hg/git thing**

### 2. Running SpiderMonkey

  After the installation is complete a folder named `mozilla-unified` should now appear in the folder your terminal was located when starting the guide above.

  Navigate into the `mozilla-unified` folder using `cd mozilla_unified`.
  
  **TODO add output**

  In order to run the SpiderMonkey engine, we first have to build it:

  ```sh
  ./mach build
  ```

  After executing this command the output should look something like this:

  ```sh
  # Show output here
  ```
  
  In order to run the finished build, execute this command:

  ```sh
  ./mach run
  ```

  Your terminal should now be in JS-loop: **TODO more info**

  ```sh
  js>
  ```

  This will be used to test our implementation throughout the tutorial.
  
  You can use it to write js-lines to evaluate.
  
  You can also run with a file: **TODO elaborate on the example**

  ```sh
  ./mach run helloworld.js
  ```

### 3. Applying simple changes

  **TODO: specify selfhosted code files located in ../builtin**

  **TODO: what is selfhosted code? different to normal js/limitations (alternatively in impl section)**

  Look at file ... and change function ... to return ...

  Test your changes by rebuilding and running the SpiderMonkey and then call the function with valid parameters.

</details>

<details>
   <summary><h2>How to Read the ECMA-262 Language Specification</h2></summary>

### 1. What is the ECMA-262 Specification?

* ECMA-262 is the official document that defines how JavaScript works. It tells developers and browser makers what JavaScript should do in every situation.

### 2. How to Navigate the Document

* **Start with the Table of Contents**: This is where you’ll find major sections like grammar, types, and functions. It helps you jump to the part you’re interested in.
* **Use Search**: The specification is large. If you’re looking for a specific topic, like “Promise” or “Array,” use your browser’s search function (`Ctrl + F`/`cmd + F`) to find it quickly.
* **Annexes (Extras)**: At the end of the document, you’ll find extra sections that explain older features or give additional context.

### 3. How to Read the Algorithms

* **Algorithms are like instructions**: The spec breaks down how JavaScript works using step-by-step instructions, almost like a recipe.
* **Steps to follow**: For example, the spec describes how `Array.prototype.push` works with small, numbered steps: first, it checks the current length, then adds the new element, and finally updates the array’s length.
* **Conditions**: You’ll often see steps like “If X is true...” which means that JavaScript checks something, and the next steps depend on the result.

### 4. Key Symbols and What They Mean

* **`[[ ]]` (Double Brackets)**: These represent internal properties of JavaScript objects. These are properties that JavaScript uses internally but developers can’t directly access.
* **`?` (Question Mark)**: This shorthand means "if this operation results in an error (abrupt completion), return that error immediately." For example, `? Call(func, arg)` means that if calling `func` with `arg` throws an error, stop the current process and return the error right away.
* **`Return`**: This marks the end of an operation, and tells you the result.
* **Keywords**: Words like `if`, `else`, or `function` follow specific rules, which are detailed in the specification.

### 5. Finding Information on Other Symbols

* The specification also uses symbols like `< >` for describing syntactic elements and different notations for describing the structure of code. To understand these symbols:
  * Look at the section called **"Notation"** in the specification, which explains the meaning of each symbol in detail.
  * For example, `<T>` in Backus-Naur Form (BNF) means a non-terminal element, which is used to describe parts of the language structure.

### 6. Start Simple

* Don’t dive into the complex parts immediately. Start by reading sections like the **Introduction** or common JavaScript features such as arrays or functions.
* **External Help**: Use resources like [SearchFox.org](https://searchfox.org/) to browse and search for JavaScript engine implementations or additional explanations before checking the more technical spec.

### 7. Example: Understanding `Array.prototype.push`

* In the specification, you can search for `Array.prototype.push` to see how it works. The algorithm will explain:
  * First, the length of the array is checked.
  * Then, the new element is added to the array.
  * Finally, the length property is updated to reflect the added element.

   **TODO first task is getting a rough understanding of the emplace spec, write line by line understamding, provide example solution**

</details>

<details>
   <summary><h2>Searchfox</h2></summary>

   When implementing a feature, Searchfox is a powerful tool. Searchfox provides an indexed view of the source code, allowing developers to efficiently search for specific files, functions, or keywords. For instance, you can trace the implementation of existing JavaScript features, see how certain functions interact with SpiderMonkey’s internal data structures, or find how built-in JavaScript objects like Map are handled. SearchFox helps you navigate a seemingly endless and confusing codebase.

   When Implementing the `emplace` proposal, you will find that looking at existing implementations of similar functionality is often a good starting point. Combine the Ecma-262 Specification with Searchfox and look at existing code.

   Example workflow:

   1. --some line from the specification--
   2. Find some other function with the same spec line in the Ecma-262 specification
   3. Look up the function in Searchfox
   4. Borrow from the other function.

</details>

<details>
   <summary><h2>Implementation</h2></summary>

### creating a function

   create a hook in `MapObject.cpp`
   **TODO simple explaination of where to hook it and why, and the hook args**

   `JS_SELF_HOSTED_FN("emplace", "MapEmplace", 2,0),`

   in `Map.js`

   ```javascript
   function MapEmplace(key, handler) {
     return 42
   }
   ```

   build to test

### implement the first line

   ```
   1. Let M be the this value.
   ```

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   }
   ```

### moving on

    The second line

   ```
   2. Perform ? RequireInternalSlot(M, [[MapData]]).
   ```

   **TODO: explain the purpose of performing internal slot**

   This step is commmon for almost all selfhosted MapObject methods. The solution is already exists in the code.

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   }
   ```

   </details>

### Line 3 - engine space and user space

  **`callfunction` vs `callcontentfunction`?**

   Why do we need to use `callFunction` and `callContentFunction`?
   In self-hosted JavaScript code, directly calling methods like map.get() is not allowed because content (external scripts)
   could modify built-in objects like Map. This could lead to unexpected behavior if a method, like get, has been changed by
   content. This scenario is called monkeyPatching.

   `callFunction` is an optimized version of `callContentfunction`, however it has a tradeoff. `callContentFunction` is
   safer when there is a potential risk of the object or method being altered it's `callFunction` is not guaranteed to work.
   **general rule**
   Use `callContentFunction` when interfering with the `this` object. In the case of this tutorial, `M`.

   Read more [here](https://udn.realityripple.com/docs/Mozilla/Projects/SpiderMonkey/Internals/self-hosting)

   self hosted code is different
     - We can use other methods written in selfhosted code
     - We can use methods methods specified in selfHosting.cpp, which are made available to selfhosted code.

   ```cpp
   // Standard builtins used by self-hosting.
   // Code snippet from SelfHosting.cpp
       JS_FN("std_Map_entries", MapObject::entries, 0, 0),
       JS_FN("std_Map_get", MapObject::get, 1, 0),
       JS_FN("std_Map_set", MapObject::set, 2, 0),
   ```

   use std_Map_entries to get the list of entry records

   ```
   3. Let entries be the List that is M.[[MapData]].
   ```

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   }
   ```

   </details>

### iterating through the map entries

   step 4 iterating through the entries

   ```
   4. For each Record { [[Key]], [[Value]] } e that is an element of entries, do
   ```

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       //...
     }
   }
   ```

   </details>

   verify that the given key is in the map if update
   perform abstract operation SameValueZero

   ```
   4a. If e.[[Key]] is not empty and SameValueZero(e.[[Key]], key) is true, then
   ```

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         //...
       }
     }
   }
   ```

   </details>

   ```
   4ai. If HasProperty(handler, "update") is true, then
   ```

   In Javascript almost "everything" is an object. All values except primitives are objects. This means we can use selfhosted
   Object methods on almost "everything".

   ```cpp
   // Code snippet from Object.cpp
   static const JSFunctionSpec object_methods[] = {
       //...
       JS_SELF_HOSTED_FN("toLocaleString", "Object_toLocaleString", 0, 0),
       JS_SELF_HOSTED_FN("valueOf", "Object_valueOf", 0, 0),
       JS_SELF_HOSTED_FN("hasOwnProperty", "Object_hasOwnProperty", 1, 0),
       //...
       JS_FS_END,
   };
   ```

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           //...
         }
       }
     }
   }
   ```

   </details>

   ```
   4ai1. Let updateFn be ? Get(handler, "update").
   ```

   get the update handler if its specified.

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           var updateFN = handler['update'];
           //...
         }
       }
     }
   }
   ```

   </details>

   ```
   4ai2. Let updated be ? Call(updateFn, handler, « e.[[Value]], key, M »).
   ```

   Use `callFunction` to call updateFN, store it as `var updated`

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           var updateFN = handler['update'];
           var updated = callFunction(updateFN, M, Value, key);
           //...
         }
       }
     }
   }
   ```

   </details>

   ```
   4ai3. Set e.[[Value]] to updated.
   ```

   Perform a set operation on the Map to update it.

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           var updateFN = handler['update'];
           var updated = callFunction(updateFN, M, Value, key);
           callContentFunction(std_Map_set, M, key, updated);
         }
       }
     }
   }
   ```

   </details>

   ```
   4aii. Return e.[[Value]].
   ```

   Now that we have updated the map, the updated value should be returned.

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           var updateFN = handler['update'];
           var updated = callFunction(updateFN, M, Value, key);
           callContentFunction(std_Map_set, M, key, updated);
         }
   
         return updated;
       }
     }
   }
   ```

   </details>

### implementing the insert handler

   ```
   5. Let insertFn be ? Get(handler, "insert").
   6. Let inserted be ? Call(insertFn, handler, « e.[[Value]], key, M »).
   7. Set e.[[Value]] to inserted.
   8. Return e.[[Value]].
   ```

   With the knowledge from implementing update, use similar techniques to implement insert.

   <details>
   <summary>Solution</summary>

   ```javascript
   function MapEmplace(key, handler) {
     var M = this;
   
     if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
       return callFunction(
         CallMapMethodIfWrapped,
         this,
         key,
         handler,
         "MapEmplace"
       );
     }
   
     var entries = callFunction(std_Map_entries, M);
   
     for (var e of allowContentIter(entries)) {
       var eKey = e[0];
       var eValue = e[1];
       
       if (SameValueZero(key, eKey)) {
         if (callFunction(Object_hasOwnProperty, handler, 'update')) {
           var updateFN = handler['update'];
           var updated = callFunction(updateFN, M, Value, key);
           callContentFunction(std_Map_set, M, key, updated);
         }
   
         return updated;
       }
     }
   
     var insertFN = handler['insert'];
     var inserted = callFunction(insertFN, key, M);
     callContentFunction(std_Map_set, M, key, inserted);
   
     return inserted;
   }
   ```

   </details>

   ...
</details>

**TODO IDEA, change to "issues with initial proposal" explaining why the old proposal was undesireable**
<details>
   <summary><h2>Issues with the original proposal</h2></summary>

The original proposal allows for a lot of flexibility, however this increases the complexity of the function, making it less likely to be used.

Simpler is often better, and it is a sufficiently common usecase to just want to insert the key-value pair if not present.

This usecase shares many similarities in functionality with other languages, where pythons `setdefault` is the most similar one.

The ability to both insert and update is not present in many other languages.

</details>

<details>
   <summary><h2>Explaining the new proposal</h2></summary>

   **What is the motivation for a new propsosal?**
   A common problem when using a Map is how to handle doing an update when you're not sure if the key already exists in the Map. This can be handled by first checking if the key is present, and then inserting or updating depending upon the result, but this is both inconvenient for the developer, and less than optimal, because it requires multiple lookups in the Map that could otherwise be handled in a single call.

   **What is the solution?**
   A method that will check whether the given key already exists in the Map. If the key already exists the value associated with the key is returned. Otherwise the key is inserted in to the map with the provided default value, then returning the newly inputted value.  

   **Simple use of "new" emplace:**

   ```js
   // Currently
let prefs = new getUserPrefs();
if (prefs.has("useDarkmode")) {
    let darkMode = prefs.get("useDarkmode");
}
else {
    prefs.set("useDarkmode", true);
    darkMode = true; //Default value
}

// Using emplace
let prefs = new getUserPrefs();
    prefs.emplace("useDarkmode", true); // Default to true
   ```

By using emplace, default values can be applied at different times, with the assurance that later defaults will not overwrite an existing value. This is obviously because the key already exists and will return the existing key instead of inserting or overwriting.

<details>
<summary>
Similar functionality in Python
</summary>
As mentioned earlier in this tutorial, there are similar functionalities in other languages such as Python and it's "setdefault" method. In our case we use emplace on Map's. The setdefault method is used on dictionaries, lets use a similar code example:

```python
# Without setdefault
prefs = {}
if "useDarkmode" not in prefs : 
  prefs["useDarkmode"] = True # Default value

dark_mode = prefs["useDarkmode"]
```

```python
# Using setdefault
prefs = {}
prefs.setdefault("useDarkmode", True)
```

</details>

</details>

<details>
    <summary><h2>Writing the new spec in ecmarkup</h2></summary>

  TODO: Installation, link to documentation of ecmarkup; <https://tc39.es/ecmarkup/>.
  * Installing Node.js and Node Package Manager
      * Windows
        1. First go to Node.js official website (<https://nodejs.org/en>), and download the Windows Installer (recommended version). 
        2. Run the installer and follow the instructions (make sure to check the box that says "Automatically install necessary tools").
        3. Verify installation by opening Command Prompt and typing:  
        ```bash
        node -v
        npm -v
        ```
        This should return the versions of Node.js and npm.
      * Mac
        1. Open Terminal
        2. Install Node.js via Homebrew by running the following command:
        ```bash
        brew install node
        ```
        3. Verify installation by typing:
        ```bash
        node -v
        npm -v
        ```
      * Linux
        1. Open Terminal
        2. Update your package list:
        ```bash
        sudo apt update
        ```
        3. Install Node.js by running:
        ```bash
        sudo apt install node.js spm
        ```
        4. Verify the installation:
        ```bash
        node -v
        npm -v
        ```
  * Installing Ecmarkup
    * Windows/Mac/Linux
      1. Open Command Prompt (Windows) or Terminal (Mac/Linux)
      2. Run the following command to install Ecmarkup globally:
      ```bash
      npm install -g ecmarkup
      ```
      3. Verify that Ecmarkup has been installed by typing:
      ```bash
      ecmarkup --version
      ```
      Now you have installed Ecmarkup! 
      
  TODO: Troubleshooting

  TODO: Explain how to translate from ecmascript to ecmarkup
  
  * The function `emplace(key, callbackfn)` in ecmarkup (can also be found under the spec folder in this proposal)
    ```emu
      <!DOCTYPE html>
      <meta charset="utf8">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/8.4/styles/github.min.css">
      <script src="./spec.js"></script>
      <pre class="metadata">
      title: Map.prototype.emplace
      stage: 2
      contributors: Erica Pramer
      </pre>

      <emu-clause id="sec-map.prototype.emplace">
        <h1>Map.prototype.emplace ( _key_, _callbackfn_ )</h1>
        <p>When the emplace method is called the following steps are taken:</p>
        <emu-alg>
          1. Let _M_ be the *this* value.
          1. Perform ? RequireInternalSlot(_M_, [[MapData]]).
          1. If IsCallable(_callbackfn_) is false, throw a *TypeError* exception.
          1. For each Record { [[Key]], [[Value]] } _e_ that is an element of _M_.[[MapData]], do:
            1. If _e_.[[Key]] is not empty and SameValueZero(_e_.[[Key]], _key_) is *true*, return _e_.[[Value]].
          1. Let _inserted_ be ? Call(_callbackfn_, _key_).
          1. Set _e_.[[Value]] to _inserted_.
          1. Return _e_.[[Value]].
        </emu-alg>
      </emu-clause>
    ```

  TODO: Building the spec
  
  TODO: Load the html file to verify successfully connected hyperlinks etc.

</details>

<details>
  <summary><h2>Implementing the new proposal</h2></summary>

  Minor changes to the implementation. Keep the same logic for line 1-4.

  **TODO fix js codeblocks, color highlighting doesn't work**

  ```

  1. Let M be the this value.
  2. Perform ? RequireInternalSlot(M, [[MapData]]).
  3. Let entries be the List that is M.[[MapData]].
  4. For each Record { [[Key]], [[Value]] } e that is an element of entries, do

  ```

  <details>
    <summary>Solution</summary>

    ```js

    function MapEmplace(key, handler) {
      var M = this;

      if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
        return callFunction(
          CallMapMethodIfWrapped,
          this,
          key,
          handler,
          "MapEmplace"
        );
      }

      var entries = callFunction(std_Map_entries, M);

      for (var e of allowContentIter(entries)) {
        var eKey = e[0];
        var eValue = e[1];

        //...
      }
    }

    ```

  </details>

  If the key is present, return the value from the key, value pair.

  ```
  4a. If e.[[Key]] is not empty and SameValueZero(e.[[Key]], key) is true, return e.[[Value]].
  ```

  <details>
    <summary>Solution</summary>

    ```javascript

    function MapEmplace(key, handler) {
      var M = this;

      if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
        return callFunction(
          CallMapMethodIfWrapped,
          this,
          key,
          handler,
          "MapEmplace"
        );
      }

      var entries = callFunction(std_Map_entries, M);

      for (var e of allowContentIter(entries)) {
        var eKey = e[0];
        var eValue = e[1];

        if (SameValueZero(eKey, key)) {
          return callContentFunction(std_Map_get, M, key);
        }
      }
    }

    ```

  </details>

  If the key was not present in the map, set the new value and then return it.

  ```
  5. Set e.[[Value]] to value.
  6. Return e.[[Value]].
  ```

  <details>
    <summary>Solution</summary>

    ```javascript

    function MapEmplace(key, value) {
      var M = this;

      if (!IsObject(M) || (M = GuardToMapObject(M)) === null) {
        return callFunction(
          CallMapMethodIfWrapped,
          this,
          key,
          value,
          "MapEmplace"
        );
      }

      var entries = callFunction(std_Map_entries, M);

      for (var e of allowContentIter(entries)) {
        var eKey = e[0];
        var eValue = e[1];

        if (SameValueZero(eKey, key)) {
          return callContentFunction(std_Map_get, M, key);
        }
      }

      callContentFunction(std_Map_set, M, key, value);

      return value;
    }

    ```

  </details>
  
</details>

<details>
   <summary><h2>Optimization</h2></summary>

  **TODO explain need for optimization, for loop iteration is slow**

  **TODO introduce std_has as a solution**

  **TODO? more advanced, next iteration introducing cpp code**

</details>

<details>

   <summary><h2>Testing</h2></summary>
   - functionality should be tested before optimization?
</details>
