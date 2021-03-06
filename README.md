# Math 514A Homeworks 6 & 7

Code for Math 514A Homeworks 6 &amp; 7

## Installation requirements
All the code is written in C++ and requires a modern compiler that supports the C++11 standard.  We tested the code with `g++ v 4.7` and `clang++ v 3.4` on Mac OS X.  The [Boost Graph Library](http://www.boost.org/doc/libs/1_55_0/libs/graph/doc/index.html) (v 1.53.0 or later) is also required.  It is convenient, but not absolutely required, to have the `cmake` (v 2.6+) and `make` utilities installed. (Many versions of `make`  will work, including GNU `make`.) It is also convenient, but not absolutely required, to have `git` installed.

If you are using a Mac and need any of these requirements, we recommend first installing [Homebrew](http://brew.sh/) and then running

      brew install git
      brew install make
      brew install cmake
      brew install g++
      brew install boost

according to your needs.

## Running the code on Linux or Mac OS X
Enter the following commands in the terminal:   

      git clone https://github.com/jon514a/homework6-7.git
      cd homework6-7 
      mkdir build
      cd build
      export CC=clang CXX=clang++
      cmake ..
      make


To run the programs that solve Problems 1.1, 1.3, 1.4, 4.7(ii), and 4.10 in Schrijver's notes, assuming your working directory is still `homework6-7/build`:  

      ./bin/p11 < ../data/p1-1.dat
      ./bin/p13 < ../data/p1-3.dat  
      ./bin/p14 < ../data/p1-4.dat
      ./bin/p47 < ../data/p4-7ii.dat
      ./bin/p410 < ../data/p4-10.dat


