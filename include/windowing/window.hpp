// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_WINDOW_HPP_
#define DISPLAY_WINDOW_HPP_

#include <windowing/window_delegate.hpp>
#include <windowing/input_manager.hpp>

namespace display {

class WindowVisitor;

// Generic windowing class which abstracts away the implementation
// details of a specific window implementation, such as GLFW. This
// allows programs to have a portable windowing system that can
// dynamically change the underlying window API without having to
// change any of the client code.
class Window {
public: 

    // Determines the windowing API to use. Currently only
    // GLFW is supported, but this can be easily extended.
    enum class Type {
        kGLFW = 0,
        kSFML = 1
    };

    // Properties with with to initialize the window.
    // Parameters:
    // name: Title of the window displayed on the top bar
    // width/height: the dimensions of the window.
    // type: the windowing implementation to use.
    struct Config {
        std::string name;
        uint32_t width;
        uint32_t height;
        Type type;
    };

    // Static function that creats a new unique instance of a
    // display window based on the provided config and with the
    // specified delegate that will be notified on window events.
    static std::unique_ptr<Window> create(const Config& config, std::weak_ptr<WindowDelegate> delegate);

    virtual ~Window() = default;

    const InputManager* input_manager() const { return input_mngr_.get(); }

    WindowDelegate& delegate() const { return *delegate_.lock(); }

    virtual void accept(WindowVisitor* visitor) = 0;
    
    virtual Type type() = 0;

    virtual void getSize(int32_t* width, int32_t* height) = 0;

    virtual void poll() = 0;

    virtual bool shouldClose() const = 0;

protected:

    Window(const Config& config, std::weak_ptr<WindowDelegate> delegate)
    : config_(config)
    , delegate_(delegate)
    , input_mngr_(std::make_unique<InputManager>())
    {}

    void updateInput() {
        input_mngr_->update();
    }

    Config config_;
    std::weak_ptr<WindowDelegate> delegate_;
    std::unique_ptr<InputManager> input_mngr_;
};

} // display

#endif // DISPLAY_WINDOW_HPP_