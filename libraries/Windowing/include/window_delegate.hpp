// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_WINDOW_DELEGATE_HPP_
#define DISPLAY_WINDOW_DELEGATE_HPP_

#include "window_types.hpp"
#include <string>
#include <stdint.h>
#include <memory>
#include <vector>
#include "input_codes.hpp"

namespace display {

// The WindowDelegate receives notifications from the |Window| class.
// A class that inherits from |WindowDelegate| can override its
// virtual member functions in order to perform specific tasks based
// on information received from the window.
class WindowDelegate : public std::enable_shared_from_this<WindowDelegate> {
public:

    // Called whenever the window is polled.s
    virtual void onUpdate() = 0;

    // Called when the window is resized. The |width| and |height|
    // parameters are the new width and height of the window.
    virtual void onResize(int32_t width, int32_t height) = 0;

    // Called when the window's position on the screen is updated.
    // The |x| and |y| parameters are the screen-space coordinates
    // of the top-left-hand corner of the window.
    virtual void onWindowMove(int32_t x, int32_t y) = 0;

    // Called when the window is initialized.
    virtual void onStart(PlatformNativeWindowHandle handle,
                         std::vector<const char*> extensions, 
                         int32_t width, int32_t height) = 0;

    // Called when the window is closed. This is a good place to perform
    // any cleanup work.
    virtual void onClose() = 0;
};

} // display

#endif // DISPLAY_WINDOW_DELEGATE_HPP_
