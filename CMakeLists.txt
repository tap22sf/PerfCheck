# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    PerfCheck
    VERSION 0.2
    DESCRIPTION "PerfCheck using cmake")

add_subdirectory(src)    # look in src subdirectory for CMakeLists.txt to process
#add_subdirectory(lib)    # look in lib subdirectory for CMakeLists.txt to process
