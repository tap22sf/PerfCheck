cmake_minimum_required(VERSION 3.11-3.18)

# Project
project(TAPLib VERSION 0.1 LANGUAGES CXX)


#
# Local sources
#
file(GLOB_RECURSE TAPLib_SOURCES "*.cpp")
file(GLOB_RECURSE TAPLib_HEADERS "*.h")

set (TAPLib_INCLUDE_DIRS "")
foreach (_headerFile ${TAPLib_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TAPLib_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES TAPLib_INCLUDE_DIRS)

add_library (TAPLib STATIC ${TAPLib_SOURCES})
target_include_directories(TAPLib PUBLIC src)

# Features
target_compile_features(TAPLib PUBLIC cxx_std_20)