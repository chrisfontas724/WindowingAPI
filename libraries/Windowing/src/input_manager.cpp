// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#include "input_manager.hpp"

namespace display {
std::map<std::string, KeyCode> InputManager::key_names_map_ = {
    { "A", KeyCode::A },
    { "B", KeyCode::B },
    { "C", KeyCode::C },
    { "D", KeyCode::D },
    { "E", KeyCode::E },
    { "F", KeyCode::F },
    { "G", KeyCode::G },
    { "H", KeyCode::H },
    { "I", KeyCode::I },
    { "J", KeyCode::J },
    { "K", KeyCode::K },
    { "L", KeyCode::L },
    { "M", KeyCode::M },
    { "N", KeyCode::N },
    { "O", KeyCode::O },
    { "P", KeyCode::P },
    { "Q", KeyCode::Q },
    { "R", KeyCode::R },
    { "S", KeyCode::S },
    { "T", KeyCode::T },
    { "U", KeyCode::U },
    { "V", KeyCode::V },
    { "W", KeyCode::W },
    { "X", KeyCode::X },
    { "Y", KeyCode::Y },
    { "Z", KeyCode::Z },

    { "Keypad0", KeyCode::_0 },
    { "Keypad1", KeyCode::_1 },
    { "Keypad2", KeyCode::_2 },
    { "Keypad3", KeyCode::_3 },
    { "Keypad4", KeyCode::_4 },
    { "Keypad5", KeyCode::_5 },
    { "Keypad6", KeyCode::_6 },
    { "Keypad7", KeyCode::_7 },
    { "Keypad8", KeyCode::_8 },
    { "Keypad9", KeyCode::_9 },
};

void InputManager::enqueueEvent(const InputEvent& event) {
    std::lock_guard<std::mutex> lock(event_mutex_);

    if (isThrottled(event)) {
        return; // Ignore the event
    }

    event_queue_.push(event);
}

bool InputManager::isThrottled(const InputEvent& event) {
    auto now = std::chrono::steady_clock::now();
    auto timeSinceLastEvent = now - last_event_time_;

    if (timeSinceLastEvent < throttle_duration_) {
        return true; // Event is within the throttle duration, so throttle it
    }

    last_event_time_ = now;
    return false; // Event is not throttled
}


} // display