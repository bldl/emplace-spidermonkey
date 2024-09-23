# Tutorial

## The `Map.prototype.emplace` proposal
What is it, how does it work, motivation and why it's needed. se [Readme i orginal ](https://github.com/tc39/proposal-upsert/blob/master/README.md)

## installing mozilla unified

### 1.1 Installation of SpiderMonkey and required tools
Naivgate in terminal to the folder you wish to place `mozilla-unified`
Different process depending on OS, look at these links.
* https://firefox-source-docs.mozilla.org/setup/linux_build.html#building-firefox-on-linux
* https://firefox-source-docs.mozilla.org/setup/linux_build.html#building-firefox-on-mac
* https://firefox-source-docs.mozilla.org/setup/linux_build.html#building-firefox-on-windows
  
When asked which version of Firefox, choose `5: SpiderMonkey JavaScript engine`.
Use hg/mercurial, but git is being tested(?).

### 1.2 Running SpiderMonkey
A folder named `mozilla-unified` should now appear in the folder your terminal was located when starting the guide.

Navigate into the `mozilla-unified` folder.

Build the SpiderMonkey engine:
```sh
$ ./mach build
```
If successful:
```sh
$ ./mach run
```
Your terminal should now be in JS-loop:
```sh
js>
```

You can use it to write js-lines to evaluate.
You can also run with a file:
```sh
./mach run helloworld.js
```


## Tools
how to read specs, how to use searchfox

## implementation
