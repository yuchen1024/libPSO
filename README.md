# PSU

## Overview

This project implements PSU

## Specifications

- OS: MAC OS x64
- Language: C++
- Requires: mcl library


## Code Structure
- README.md

- CMakeLists.txt

- /bin: (executable file) 

- /common: 
  * print.hpp --- define print function
  * routines.hpp

- /src: source files
  * ElGamal.hpp: implement ElGamal PKE

- /test: test files
  * test_PSU.cpp

- /build: build files

## Install dependent lib mcl 
download [mcl](https://github.com/herumi/mcl), then
```
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  $ sudo make install
```

## Compile and Run
```
  $ cd build
  $ cmake ..
  $ make
```
Then you can find the exe files under /bin

## Updates
This repo is obsoleted due to its immaturity. 
We refer to https://github.com/yuchen1024/Kunlun/mpc for a neat and efficient implementation. 


