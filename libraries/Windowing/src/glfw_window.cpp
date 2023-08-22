// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif // _WIN32
#include "glfw_window.hpp"
#include "input_codes.hpp"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <map>

namespace display {

struct GLFWWindow::Impl {
    GLFWwindow* window;

    ~Impl() {
        glfwDestroyWindow(window);
    }
};

namespace {

static bool is_initialized = false;

struct Initializer {
    Initializer() {
        if (glfwInit() == TRUE) {
            is_initialized = true;
        }
    }
};

static Initializer initializer_;

static std::map<uint32_t, KeyCode> key_mapping = {
    // Letter keys.
    {GLFW_KEY_A, KeyCode::A},
    {GLFW_KEY_B, KeyCode::B},
    {GLFW_KEY_C, KeyCode::C},
    {GLFW_KEY_D, KeyCode::D},
    {GLFW_KEY_E, KeyCode::E},
    {GLFW_KEY_F, KeyCode::F},
    {GLFW_KEY_G, KeyCode::G},
    {GLFW_KEY_H, KeyCode::H},
    {GLFW_KEY_I, KeyCode::I},
    {GLFW_KEY_J, KeyCode::J},
    {GLFW_KEY_K, KeyCode::K},
    {GLFW_KEY_L, KeyCode::L},
    {GLFW_KEY_M, KeyCode::M},
    {GLFW_KEY_N, KeyCode::N},
    {GLFW_KEY_O, KeyCode::O},
    {GLFW_KEY_P, KeyCode::P},
    {GLFW_KEY_Q, KeyCode::Q},
    {GLFW_KEY_R, KeyCode::R},
    {GLFW_KEY_S, KeyCode::S},
    {GLFW_KEY_T, KeyCode::T},
    {GLFW_KEY_U, KeyCode::U},
    {GLFW_KEY_V, KeyCode::V},
    {GLFW_KEY_W, KeyCode::W},
    {GLFW_KEY_X, KeyCode::X},
    {GLFW_KEY_Y, KeyCode::Y},
    {GLFW_KEY_Z, KeyCode::Z},

    // Number keys.
    {GLFW_KEY_0, KeyCode::_0},
    {GLFW_KEY_1, KeyCode::_1},
    {GLFW_KEY_2, KeyCode::_2},
    {GLFW_KEY_3, KeyCode::_3},
    {GLFW_KEY_4, KeyCode::_4},
    {GLFW_KEY_5, KeyCode::_5},
    {GLFW_KEY_6, KeyCode::_6},
    {GLFW_KEY_7, KeyCode::_7},
    {GLFW_KEY_8, KeyCode::_8},
    {GLFW_KEY_9, KeyCode::_9},

    // Shift and others.
    {GLFW_KEY_LEFT_SHIFT, KeyCode::LeftShift},
    {GLFW_KEY_RIGHT_SHIFT, KeyCode::RightShift},
};

static std::map<uint32_t, InputEventType> action_mapping = {
    {GLFW_PRESS,   InputEventType::KeyPressed},
    {GLFW_RELEASE, InputEventType::KeyReleased},
};

static void framebufferResizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    wrapper->delegate().onResize(width, height);
}   

static void windowPositionCallback(GLFWwindow* window, int32_t x, int32_t y) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    wrapper->delegate().onWindowMove(x,y);
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    InputEvent event; 
    event.type = InputEventType::MouseMoved;
    event.mouseX = xpos;
    event.mouseY = ypos;
    wrapper->input_manager()->enqueueEvent(event);
}

static void keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    InputEvent event; 
    event.type = action_mapping[action];
    event.key = key_mapping[key];
    wrapper->input_manager()->enqueueEvent(event);
}

static void mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {

}

void monitorCallback(GLFWmonitor* monitor, int event) {
    std::cerr << "Monitor callback called for monitor " << glfwGetMonitorName(monitor) << std::endl;
    if (event == GLFW_CONNECTED) {
        // TODO: The monitor was connected
    }
    else if (event == GLFW_DISCONNECTED) {
        // TODO: The monitor was disconnected
    }
}

void scrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
}


static void windowCloseCallback(GLFWwindow* window) {
    auto wrapper = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    wrapper->terminate();
}

} // anonymous namespace

GLFWWindow::GLFWWindow(const Config& config, std::weak_ptr<WindowDelegate> del)
        : Window(config, del) {

    if (!is_initialized) {
        throw std::runtime_error("GLFW not initialized. Abort");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
    
    impl_ = std::make_unique<Impl>();
    impl_->window = glfwCreateWindow(config_.width, config_.height, config_.title.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(impl_->window, this);
    glfwSetFramebufferSizeCallback(impl_->window, framebufferResizeCallback);
    glfwSetWindowPosCallback(impl_->window, windowPositionCallback);
    glfwSetCursorPosCallback(impl_->window, cursorPositionCallback);
    glfwSetKeyCallback(impl_->window, keyCallback);
    glfwSetMouseButtonCallback(impl_->window, mouseButtonCallback);
    glfwSetScrollCallback(impl_->window, scrollCallback);
    glfwSetWindowCloseCallback(impl_->window, windowCloseCallback);
    glfwSetMonitorCallback(monitorCallback);
}

GLFWWindow::~GLFWWindow() {
    impl_.reset();
}

void GLFWWindow::start() {
    int32_t width, height;
    getSize(&width, &height);
    delegate().onStart(getNativeWindowHandle(), getExtensions(), width, height);
}

void GLFWWindow::terminate() {
    delegate().onClose();
}

std::vector<const char*> GLFWWindow::getExtensions() const {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}

void GLFWWindow::getSize(int32_t* width, int32_t* height) const {
    glfwGetFramebufferSize(impl_->window, width, height);
}

void GLFWWindow::poll() {
    glfwPollEvents();
    delegate().onUpdate();
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(impl_->window);
}

PlatformNativeWindowHandle GLFWWindow::getNativeWindowHandle() const {
#ifdef _WIN32
    return glfwGetWin32Window(impl_->window);
#elif defined(__linux__)
    return glfwGetX11Window(impl_->window);
#elif defined(__APPLE__)
    return glfwGetCocoaWindow(impl_->window);
#else
    return nullptr; // Handle other platforms if needed
#endif
}

} // display
