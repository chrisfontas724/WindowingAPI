// Copyright 2020 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef WINDOWING_WINDOW_VISITOR_HPP_
#define WINDOWING_WINDOW_VISITOR_HPP_

namespace display {

class GLFWWindow;
struct WindowVisitor {
    virtual void visit(GLFWWindow* window) = 0;
};

} // display

#endif // WINDOWING_WINDOW_VISITOR_HPP_
