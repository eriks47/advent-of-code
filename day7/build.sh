#!/bin/sh

set -xe

g++ -c Path.cpp
g++ -c Tree.cpp
g++ directories.cpp Path.o Tree.o
./a.out
