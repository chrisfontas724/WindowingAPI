// Copyright 2023 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_PLATFORM_HPP_
#define DISPLAY_PLATFORM_HPP_

#include "window.hpp"
#include <queue>

namespace display {

class Platform {
public:

    Platform(Window::Config config, std::shared_ptr<WindowDelegate> delegate);
    ~Platform();

    void runEventLoop();

    std::queue<InputEvent> getInputEvents();

    const Window* getWindow() const;

private:
    std::unique_ptr<Window> window_;
};

} // display

#endif // DISPLAY_PLATFORM_HPP_