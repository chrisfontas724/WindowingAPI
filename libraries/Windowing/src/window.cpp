// Copyright 2023 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#include "window.hpp"

//namespace display {
#ifdef _WIN32
#include <windows.h>
using PlatformNativeWindowHandle = HWND;
#elif defined(__linux__)
#include <xcb/xcb.h>
using PlatformNativeWindowHandle = xcb_window_t;
#elif defined(__APPLE__)
#import <AppKit/NSView.h>
using PlatformNativeWindowHandle = NSView*;
// Add other platform-specific types as needed
#endif
//} // namespace display