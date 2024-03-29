// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#include "platform.hpp"
#include "stdio.h"
#include <iostream>

// Example dummy delegate class.
class Delegate : public display::WindowDelegate {
public:
    
    // |WindowDelegate|
    void onUpdate() override { std::cout << "onUpdate" << std::endl; }
    
    void onResize(int32_t width, int32_t height) override {
        std::cout << "onResize" << std::endl;
    }
    
    void onWindowMove(int32_t x, int32_t y) override {
        std::cout << "onWindowMove" << std::endl;
    }
    
    void onStart(PlatformNativeWindowHandle handle,
                 std::vector<const char*> extensions,
                 int32_t width, int32_t height) override {
        std::cout << "onStart" << std::endl;
    }
    
    void onClose() override {
        std::cout << "onClose" << std::endl;
    }
};

// Example InputManager checks.
void checkInput(const display::InputManager* input) {
    // if (input->key(display::KeyCode::A)) {
    //     std::cout << "Pressed 'A'" << std::endl;
    // } else if (input->key(display::KeyCode::B)) {
    //     std::cout << "Pressed 'B'" << std::endl;
    // } else if (input->key(display::KeyCode::C)) {
    //     std::cout << "Pressed 'C'" << std::endl;
    // }
    // etc...
}

// Set up a window with the delegate and start polling.
int main(int arg, char** argv) {
    
    display::Window::Config config;
    config.title = "Window Example";
    config.width = 1024;
    config.height = 768;
    auto delegate = std::make_shared<Delegate>();

    auto platform = std::make_unique<display::Platform>(config, delegate);
    platform->runEventLoop();
    return 0;
}

