// Copyright 2023 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#include "platform.hpp"
#include "glfw_window.hpp"

namespace display {

Platform::Platform(Window::Config config, std::shared_ptr<WindowDelegate> delegate) {
    window_ = std::make_unique<GLFWWindow>(config, delegate);
}

Platform::~Platform() {
    window_.reset();
}

void Platform::runEventLoop() {
    window_->start();

    while (!window_->shouldClose()) {
        window_->poll();
    }
}

const Window* Platform::getWindow() const {
    return window_.get();
}

std::queue<InputEvent> Platform::getInputEvents() {
    return window_->input_manager()->getInputEvents();
}


} // display