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

    void enqueueEvent(const InputEvent& event);

    std::queue<InputEvent> getInputEvents();

private:
    friend class Window;
    static std::map<std::string, KeyCode> key_names_map_;

    std::queue<InputEvent> event_queue_;
    std::mutex event_mutex_;
    std::chrono::steady_clock::time_point last_event_time_;
    const std::chrono::milliseconds throttle_duration_ = std::chrono::milliseconds(200); 

    bool isThrottled(const InputEvent& event);

};

} // display


#endif // DISPLAY_INPUT_MANAGER_HPP_
