# Tutorial

<details>
  <summary><h2>The `Map.prototype.emplace` proposal</h2></summary>
  
  **TODO code examples**

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

</details>

<details>
  <summary><h2>Installing mozilla unified</h2></summary>

  In this section you will learn how to download the Mozilla environment based on your OS. It will also feature setting up SpiderMonkey for development and introduce main tools which are used during development.

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
  $ ./mach build
  ```
  After executing this command the output should look something like this:
  ```sh
  $ # Show output here
  ```
  
  In order to run the finished build, execute this command:
  ```sh
  $ ./mach run
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

  **TODO Should we also have an exercise?**

</details>

<details>
  <summary><h2>How to Read the ECMA-262 Language Specification</h2></summary>

  ### 1. What is the ECMA-262 Specification?
  - ECMA-262 is the official document that defines how JavaScript works. It tells developers and browser makers what JavaScript should do in every situation.

  ### 2. How to Navigate the Document
  - **Start with the Table of Contents**: This is where you’ll find major sections like grammar, types, and functions. It helps you jump to the part you’re interested in.
  - **Use Search**: The specification is large. If you’re looking for a specific topic, like “Promise” or “Array,” use your browser’s search function (`Ctrl + F`) to find it quickly. 
  - **Annexes (Extras)**: At the end of the document, you’ll find extra sections that explain older features or give additional context.

  ### 3. How to Read the Algorithms
  - **Algorithms are like instructions**: The spec breaks down how JavaScript works using step-by-step instructions, almost like a recipe.
  - **Steps to follow**: For example, the spec describes how `Array.prototype.push` works with small, numbered steps: first, it checks the current length, then adds the new element, and finally updates the array’s length.
  - **Conditions**: You’ll often see steps like “If X is true...” which means that JavaScript checks something, and the next steps depend on the result.

  ### 4. Key Symbols and What They Mean
  - **`[[ ]]` (Double Brackets)**: These represent internal properties of JavaScript objects. These are properties that JavaScript uses internally but developers can’t directly access.
  - **`?` (Question Mark)**: This shorthand means "if this operation results in an error (abrupt completion), return that error immediately." For example, `? Call(func, arg)` means that if calling `func` with `arg` throws an error, stop the current process and return the error right away.
  - **`Return`**: This marks the end of an operation, and tells you the result.
  - **Keywords**: Words like `if`, `else`, or `function` follow specific rules, which are detailed in the specification.

  ### 5. Finding Information on Other Symbols
  - The specification also uses symbols like `< >` for describing syntactic elements and different notations for describing the structure of code. To understand these symbols:
    - Look at the section called **"Notation"** in the specification, which explains the meaning of each symbol in detail.
    - For example, `<T>` in Backus-Naur Form (BNF) means a non-terminal element, which is used to describe parts of the language structure.
    
  ### 6. Start Simple
  - Don’t dive into the complex parts immediately. Start by reading sections like the **Introduction** or common JavaScript features such as arrays or functions.
  - **External Help**: Use resources like [SearchFox.org](https://searchfox.org/) to browse and search for JavaScript engine implementations or additional explanations before checking the more technical spec. 

  ### 7. Example: Understanding `Array.prototype.push`
  - In the specification, you can search for `Array.prototype.push` to see how it works. The algorithm will explain:
    - First, the length of the array is checked.
    - Then, the new element is added to the array.
    - Finally, the length property is updated to reflect the added element.

  **TODO first task is getting a rough understanding of the emplace spec, write line by line understamding, provide example solution**
</details>


<details>
  <summary><h2>Tools</h2></summary>
  
  how to read specs, how to use searchfox
  
</details>

<details>
  <summary><h2>Implementation</h2></summary>  

  ### creating a function

  create a hook in `MapObject.cpp`

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
  explain the purpose of performing internal slot

  borrow from ForEach

  ```
  2. Perform ? RequireInternalSlot(M, [[MapData]]).
  ```

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

  self hosted code is different

  ```cpp
  // Standard builtins used by self-hosting.
      JS_FN("std_Map_entries", MapObject::entries, 0, 0),
      JS_FN("std_Map_get", MapObject::get, 1, 0),
      JS_FN("std_Map_set", MapObject::set, 2, 0),
  ```

  use std_Map_entries to get the list of entry records

  ```
  3. Let entries be the List that is M.[[MapData]].
  ```

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

  step 4 iterating through the entries

  ```
  4. For each Record { [[Key]], [[Value]] } e that is an element of entries, do
  ```

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

  verify that the given key is in the map if update
  perform abstract operation SameValueZero

  ```
  4a. If e.[[Key]] is not empty and SameValueZero(e.[[Key]], key) is true, then
  ```

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

  ...
</details>
<details>
  <summary><h2>Changes to the proposal</h2></summary>
</details>
<details>
  <summary><h2>Explaining the new proposal</h2></summary>
  - simplicity over functionality etc

</details>
<details>
  <summary><h2>Writing the new spec in ecmarkup</h2></summary>
</details>
<details>
  <summary><h2>implementing the new proposal</h2></summary>
</details>
<details>
  <summary><h2>optimization</h2></summary>
</details>
<details>
  <summary><h2>Testing</h2></summary>
   - functionality should be tested before optimization?
</details>

