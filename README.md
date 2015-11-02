# Whats this 

This package illsutrates a error on GCC 4.2 
Run this example on a regular ubuntu15.10

Needed deps:
`sudo apt-get install libboost-math-dev`


Run the makefile to see a chrasing component:
`make test1`


Note that all other target success without any problems:
`make test2` Removed -O2
`make test3` Compile both with c++11
`make test4` Compile both without c++11
`make test5` (optional) compilation like test1 with clang (needs `sudo apt-get install llvm-3.4`)

Tested on a fresh ubuntu15.10 and debian testing system.
Compiler on Debian Testing: gcc-5.2.1-22 5.2.1 20151010

