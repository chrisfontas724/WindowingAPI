// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_INPUT_CODES_HPP_
#define DISPLAY_INPUT_CODES_HPP_

namespace display {

enum class KeyCode {
    A, B, C, D, E, F,
    G, H, I, J, K, L,
    M, N, O, P, Q, R,
    S, T, U, V, W, X,
    Y, Z, _0, _1, _2, 
    _3, _4, _5, _6,
    _7, _8, _9, Space,
    LeftShift, RightShift,
};

enum class InputEventType {
    KeyPressed,
    KeyReleased,
    MouseLeftButtonClicked,
    MouseRightButtonClicked,
    MouseMoved,
};

struct InputEvent {
    InputEventType type;
    KeyCode key;   
    double mouseX; // Mouse X position (valid for MouseMoved events)
    double mouseY; // Mouse Y position (valid for MouseMoved events)
    // Add other data members as needed
};


} // display

#endif // DISPLAY_INPUT_CODES_HPP_