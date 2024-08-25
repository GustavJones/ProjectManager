# Project Manager

A simple C++ CLI tool to create and delete projects from user-defined templates.

# Usage

Run ProjectManager with `--help` to display all available arguments and their structure

# Building

Requirements:
- CMake
- C++ compiler for Linux (Tested with g++)

Clone the repository with `git clone --recursive https://github.com/GustavJones/ProjectManager.git` to get the source code with submodules.
Run `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` folowed by `cmake --build build` to compile the project.
