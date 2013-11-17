#Math 514A Homeworks 6 & 7#

Code for Math 514A Homeworks 6 &amp; 7

# Installation Requirements #
All the code is written in C++ and requires a modern compiler that supports the C++11 standard.  (We tested the code with `g++ v 4.7` and `clang++ v 5.0` work on Mac OS X.)  The Boost Graph Library (v 1.54.0 or later) is also required.  It is useful, but not absolutely required, to have the `cmake` (v 2.6+) and `make` (many versions will work) utilities installed.

If you are using a Mac and need any of these requirements, we recommend first installing [Homebrew](http://brew.sh/) and then running 
`brew install make`, `brew install g++`, `brew install boost`, and `brew install cmake`, according to your needs.

# Installation Instructions on Linux or Mac OS X #
1. Clone this repo: `git clone https://github.com/jon514a/homework6-7.git`

2. `cd homework6-7` (or whatever you named the repo)

3. `mkdir build`

4. `cd build`

5. `cmake ..`

6. `make`

7. To run the four programs that produce the code for Problems 1.1, 1.3, 1.4, and 4.7(ii), assuming your working directory is still `homework6-7/build`:
  `./bin/p11 < ../data/p1-1.dat`
  `./bin/p13 < ../data/p1-3.dat`
  `./bin/p14 < ../data/p1-4.dat`
  `./bin/p4-7ii < ../data/p4-7ii.dat`

