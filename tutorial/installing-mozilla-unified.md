# Installing Mozilla Unified

## Table of Contents
- [intro](README.md)
- [The `Map.prototype.emplace` proposal](tutorial/initial-proposal.md)
- [Installing mozilla unified](tutorial/installing-mozilla-unified.md)
- [Get to know the tools](tutorial/tools.md)
- [How to Read the ECMA-262 Language Specification](tutorial/reading-Ecma262-specs.md)
- [implementing the proposal](tutorial/implementation.md)

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