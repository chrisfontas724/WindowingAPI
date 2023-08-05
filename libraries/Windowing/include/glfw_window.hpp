// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_GLFW_WINDOW_HPP_
#define DISPLAY_GLFW_WINDOW_HPP_

#include "window.hpp"
#include <vulkan/vulkan.hpp>

namespace display {

// Wrapper around the GLFW Window API, which also inherits
// from |Window|. Clients should not use this class directly
// but should interface with it through |Window|. 
class GLFWWindow : public Window{
public: 

    GLFWWindow(const Config& config, std::weak_ptr<WindowDelegate> delegate);

    ~GLFWWindow() override;

    // |Window||
    void accept(WindowVisitor* visitor) override;

    // |Window|
    void getSize(int32_t* width, int32_t* height) override;

    // |Window|
    void poll() override;

    // |Window|
    bool shouldClose() const override;

    void set_title(const std::string& title) override;
    
    bool supports_vulkan();

    std::vector<const char*> getExtensions() const;

    vk::SurfaceKHR createVKSurface(const vk::Instance& instance);

protected:

    GLFWWindow() = delete;

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // display

#endif // DISPLAY_WINDOW_HPP_