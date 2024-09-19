# The JoTang Compiler Infrastructure

Welcome to the this project!

## Getting Started

**warning!**    if If you are still programming in a Windows environment, immediately set up a Linux environment (via VirtualBox/WSL) or switch to macOS to continue this project.

```shell
#make sure you are already install cmake,ninja,build_essensial
sudo apt update
sudo apt install -y cmake ninja-build build-essential llvm clang 
```

use **git to clone**

```shell
git clone https://github.com/llvm/llvm-project.git
mkdir build && cd build
cmake -GNinja ..
ninja
```

now you will find this compiler in ./build

## how to use this compiler

Here is an example we provided for you to use. **Try this.**

```shell
#Compile the source code test.c into an IR file named test.c.ll
./build/SYSY-compiler ./function_test/test.c ./function_test/test.c.ll
#Compile the source code use mem2reg opt
./build/SYSY-compiler ./function_test/test.c --mem2reg ./function_test/test.c.ll
```

After getting the IR file test.c.ll, The most important thing we should do is to **Verify correctness. (It happens when you finish writing a pass and have generated an IR.)** 

```shell
#you can use LLVM lli tool to check this
lli ./function_test/test.c.ll
#if wrong ,try this
lli -opaque-pointers ./function_test/test.c.ll
```

Right Form:

```less
//如果存在output会直接打印
TOTAL: 0H-0M-0S-0us
//input "echo $?" to check the return number  
```

Check the **interface**, Go to : 