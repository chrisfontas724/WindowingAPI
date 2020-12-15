# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW")
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

set(HEADER_LIST 
    "${Windowing_SOURCE_DIR}/include/windowing/input_codes.hpp" 
    "${Windowing_SOURCE_DIR}/include/windowing/input_manager.hpp"
    "${Windowing_SOURCE_DIR}/include/windowing/window_delegate.hpp"
    "${Windowing_SOURCE_DIR}/include/windowing/window.hpp")


# Make an automatic library - will be static or dynamic based on user setting
add_library(windowing 
    glfw_window.cpp
    input_manager.cpp
    ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(windowing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)

target_link_libraries(windowing PUBLIC Vulkan::Vulkan glfw)


# All users of this library will need at least C++11
target_compile_features(windowing PUBLIC cxx_std_11)


# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
