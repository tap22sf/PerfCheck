# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    TAPLib
    VERSION 1.0
    DESCRIPTION "TAP Library")

add_subdirectory(src)    # look in src subdirectory for CMakeLists.txt to process
