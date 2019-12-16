# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

#include "display/window.hpp"
#include "stdio.h"

class Delegate : public display::WindowDelegate {
public:
    
    // |WindowDelegate|
    void onUpdate() override { std::cout << "onUpdate" << std::endl; }
    
    void onResize(int32_t width, int32_t height) override {}
    
    void onWindowMove(int32_t x, int32_t y) override {}
    
    void onStart(display::Window*) override {}
    
    void onClose() override {}
};

int main(int arg, char** argv) {
    
    display::Window::Config config;
    config.name = "Window Example"
    config.width = config_.start_resolution_x;
    config.height = config_.start_resolution_y;
    config.type =  display::Window::Type::kGLFW;
    auto window = display::Window::create(config, std::make_shared<Delegate>());
    
    while (!window->shouldClose()) {
        window->poll();
    }

    return 0;
}

