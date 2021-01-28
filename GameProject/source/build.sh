#!/bin/bash

# building the whole project

echo "starting build process..."
g++ -g -o ../debug/gameproject.o Classes.cpp dungeon.cpp events.cpp Main.cpp init.cpp
echo "build process finished"
