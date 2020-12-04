// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#include <windowing/window.hpp>
#include "glfw_window.hpp"
#include <iostream>

namespace display {

std::unique_ptr<Window> Window::create(const Window::Config& config, std::weak_ptr<WindowDelegate> delegate) {

    // Make sure the config has valid data.
    if (config.name.length() <= 0 ||
        config.width <= 0 ||
        config.height <= 0) {
        std::cerr << "Invalid window config: " << config.name
                  << " " << config.width << " " << config.height << std::endl;
    }

    // Return a valid window type depending on the API used by the engine
    switch (config.type) {
        case Type::kGLFW:
            return std::make_unique<GLFWWindow>(config, delegate);
        case Type::kSFML:
        default:
            std::cerr << "Valid API type not found!" << std::endl;
            return nullptr;
    }
}


} // display
