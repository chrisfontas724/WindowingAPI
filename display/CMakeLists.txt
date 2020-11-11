# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

add_library (display
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input_manager.cpp
)

set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW")
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(display Vulkan::Vulkan glfw)
target_include_directories(display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

