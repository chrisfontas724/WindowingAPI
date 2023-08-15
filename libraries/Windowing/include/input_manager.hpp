// Copyright 2023 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_INPUT_MANAGER_HPP_
#define DISPLAY_INPUT_MANAGER_HPP_

#include "input_codes.hpp"
#include <queue>
#include <chrono>
#include <mutex>
#include <map>

namespace display {

class InputManager {
public:

    void enqueueEvent(const InputEvent& event) {
        std::lock_guard<std::mutex> lock(event_mutex_);

        if (isThrottled(event)) {
            return; // Ignore the event
        }

        event_queue_.push(event);
    }

    std::queue<InputEvent> getInputEvents() {
        std::lock_guard<std::mutex> lock(event_mutex_);
        std::queue<InputEvent> events = std::move(event_queue_);
        return events;
    }

private:
    friend class Window;
    static std::map<std::string, KeyCode> key_names_map_;

    std::queue<InputEvent> event_queue_;
    std::mutex event_mutex_;

    bool isThrottled(const InputEvent& event) {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceLastEvent = now - last_event_time_;

        if (timeSinceLastEvent < throttle_duration_) {
            return true; // Event is within the throttle duration, so throttle it
        }

        last_event_time_ = now;
        return false; // Event is not throttled
    }

    std::chrono::steady_clock::time_point last_event_time_;
    const std::chrono::milliseconds throttle_duration_ = std::chrono::milliseconds(200); 
};

} // display


#endif // DISPLAY_INPUT_MANAGER_HPP_
