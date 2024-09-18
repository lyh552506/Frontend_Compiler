# The JoTang Compiler Infrastructure

Welcome to the this project!

## Getting Started

warning! if If you are still programming in a Windows environment, immediately set up a Linux environment (via VirtualBox/WSL) or switch to macOS to continue this project.

```shell
#make sure you are already install cmake,ninja,build_essensial
sudo apt update
sudo apt install -y cmake ninja-build build-essential
```

use git to clone

```shell
git clone https://github.com/llvm/llvm-project.git
mkdir build && cd build
cmake -GNinja ..
ninja
```

now you will find this compiler in ./build

