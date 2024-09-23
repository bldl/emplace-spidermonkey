# Tutorial

## The `Map.prototype.emplace` proposal
What is it, how does it work, motivation and why it's needed. se [Readme i orginal ](https://github.com/tc39/proposal-upsert/blob/master/README.md)


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

## Installing mozilla unified

Installing Mozilla Unified and other tools.
Specific instructions for different OS by link.
hg/mercurial or git.
Building and running the engine.
Changing the code and rebuild.


## Tools
how to read specs, how to use searchfox

## implementation
