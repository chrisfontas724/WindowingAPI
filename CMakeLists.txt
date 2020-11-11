# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

cmake_minimum_required (VERSION 3.7)

# Set Project name.
project (WindowDemo)

# C++ Compiler Settings.
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "-std=gnu++17")

# Set the include directories.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(/usr/include)

# Create main executable.
add_executable(WindowDemo main.cpp)

add_subdirectory(display)
target_link_libraries(WindowDemo display)
