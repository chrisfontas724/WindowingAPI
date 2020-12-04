// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_GLFW_WINDOW_HPP_
#define DISPLAY_GLFW_WINDOW_HPP_

#include "windowing/window.hpp"

namespace display {

// Wrapper around the GLFW Window API, which also inherits
// from |Window|. Clients should not use this class directly
// but should interface with it through |Window|. 
class GLFWWindow : public Window{
public: 

    GLFWWindow(const Config& config, std::weak_ptr<WindowDelegate> delegate);

    ~GLFWWindow() override;

    // |Window|
    Type type() override { return Type::kGLFW; }

    // |Window|
    void getSize(int32_t* width, int32_t* height) override;

    // |Window|
    void poll() override;

    // |Window|
    bool shouldClose() const override;
    
    // |Window|
    bool supports_vulkan() override;

    // |Window|
    std::vector<const char*> getExtensions() const override;

    // |Window|
    vk::SurfaceKHR createVKSurface(const vk::Instance& instance) override;

protected:

    GLFWWindow() = delete;

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // display

#endif // DISPLAY_WINDOW_HPP_