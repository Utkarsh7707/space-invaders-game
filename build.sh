#!/bin/bash

# Set the source files
SOURCE_FILES="main.cpp spaceShip.cpp game.cpp laser.cpp block.cpp obstacle.cpp alien.cpp mystry.cpp"

# Set the output binary name
OUTPUT_BINARY="game"

# Compiler and linker flags
CXX=g++
CXXFLAGS="-std=c++11 -Wall"
LDFLAGS="-lraylib -lm -lpthread -ldl -lrt -lX11"

# Compile and link the program
$CXX $CXXFLAGS $SOURCE_FILES -o $OUTPUT_BINARY $LDFLAGS

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Running the program..."
    ./game
else
    echo "Build failed!"
    exit 1
fi