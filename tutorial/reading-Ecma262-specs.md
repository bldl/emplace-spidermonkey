# How to Read the ECMA-262 Language Specification

## Table of Contents
- [intro](../README.md)
- [The `Map.prototype.emplace` proposal](./initial-proposal.md)
- [Installing mozilla unified](./installing-mozilla-unified.md)
- [Get to know the tools](./tools.md)
- [How to Read the ECMA-262 Language Specification](./reading-Ecma262-specs.md)
- [implementing the proposal](./implementation.md)

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