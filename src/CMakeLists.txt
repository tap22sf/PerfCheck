cmake_minimum_required(VERSION 3.11-3.18)

# Project
project(PerfCheck VERSION 0.1 LANGUAGES CXX)


# Qt
find_package(Qt5 COMPONENTS Core Gui Widgets Charts Printsupport REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR "YES")
set(CMAKE_AUTOMOC "YES")
set(CMAKE_AUTOUIC "YES")

# Boost
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_INCLUDE_DIR "F:\\Middleware\\boost_1_75_0")
find_package(Boost 1.75.0 REQUIRED Regex)

# TAPLib
add_library(TAPLib STATIC IMPORTED)
set_target_properties(TAPLib PROPERTIES IMPORTED_LOCATION "F:\\Local\\TapLib\\build\\src\\Debug\\TAPLib.lib")
set_target_properties(TAPLib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "F:\\Local\\TapLib\\src")

#
# Local sources
#
configure_file(PerfCheckVersion.h.in ../src/PerfCheckVersion.h )
file(GLOB_RECURSE PerfCheck_SOURCES "*.cpp")
file(GLOB_RECURSE PerfCheck_UI "*.ui")
file(GLOB_RECURSE PerfCheck_HEADERS "*.h")

set (PerCheck_INCLUDE_DIRS "")
foreach (_headerFile ${PerfCheck_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PerfCheck_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES PerfCheck_INCLUDE_DIRS)


# Build the .exe
add_executable (PerfCheck ${PerfCheck_SOURCES} ${PerfCheck_HEADERS} ${PerfCheck_UI})

# Link dependencies
target_link_libraries (PerfCheck
        TAPLib
        Boost::Regex
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::PrintSupport
        Qt5::Charts)

# Features
target_compile_features(PerfCheck PUBLIC cxx_std_20)

