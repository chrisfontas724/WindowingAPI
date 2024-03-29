// Copyright 2023 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_WINDOW_HPP_
#define DISPLAY_WINDOW_HPP_

#include "window_delegate.hpp"
#include "input_manager.hpp"
#include <vector>

namespace display {

// Generic windowing class which abstracts away the implementation
// details of a specific window implementation, such as GLFW. This
// allows programs to have a portable windowing system that can
// dynamically change the underlying window API without having to
// change any of the client code.
class Window {
public: 

    // Properties with with to initialize the window.
    // Parameters:
    // name: Title of the window displayed on the top bar
    // width/height: the dimensions of the window.
    // type: the windowing implementation to use.
    struct Config {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    virtual ~Window() = default;

    InputManager* input_manager() { return input_mngr_.get(); }
    WindowDelegate& delegate() { return *delegate_.lock(); }

    virtual void start() = 0;

    virtual void terminate() = 0;

    virtual void getSize(int32_t* width, int32_t* height) const = 0;

    virtual void poll() = 0;

    virtual bool shouldClose() const = 0;

protected:

    Window(const Config& config, std::weak_ptr<WindowDelegate> delegate)
    : config_(config)
    , delegate_(delegate)
    , input_mngr_(std::make_unique<InputManager>())
    {}

    Config config_;
    std::weak_ptr<WindowDelegate> delegate_;
    std::unique_ptr<InputManager> input_mngr_;
};

} // display

#endif // DISPLAY_WINDOW_HPP_