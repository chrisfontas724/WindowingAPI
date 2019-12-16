// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef DISPLAY_INPUT_MANAGER_HPP_
#define DISPLAY_INPUT_MANAGER_HPP_

#include "display/input_codes.hpp"
#include <string>
#include <map>
#include <set>

namespace display {

// Input manager with portable key representations. Is used in
// conjunction with the |Window| class so that the key codes
// for any one particular window API, such as GLFW or SFML are
// both mapped onto the same key codes used here, allowing for
// client code to stay the same even when changing the underlying
// windowing API.
class InputManager {
public:

    static const std::map<std::string, KeyCode>& key_names_map() {
        return key_names_map_;
    }

    void set_mouse_position(float x, float y) {
        mouse_position_ = std::make_pair(x,y);
    }

    float mouse_x() const {
        return mouse_position_.first;
    }

    float mouse_y() const {
        return mouse_position_.second;
    }

    void set_key_and_action(KeyCode key, KeyAction action) {
        key_action_map_[action].insert(key);
        if (action != KeyAction::kRepeat) {
            key_state_map_[key] = action;
        }
    }

    bool key(KeyCode key) const {
        return key_state_map_.count(key) && key_state_map_.at(key) == KeyAction::kPressed;
    }

    bool key_down(KeyCode key) const {
        if (!key_action_map_.count(KeyAction::kPressed)) {
            return false;
        }
        auto& set = key_action_map_.at(KeyAction::kPressed);
        return set.find(key) != set.end();
    }

    bool key_up(KeyCode key) const {
        if (!key_action_map_.count(KeyAction::kReleased)) {
            return false;
        }
        auto& set = key_action_map_.at(KeyAction::kReleased);
        return set.find(key) != set.end();
    }

    uint32_t pending_actions() {
        return key_action_map_.size();
    }

private:
    friend class Window;

    std::map<KeyAction, std::set<KeyCode>> key_action_map_;
    std::map<KeyCode, KeyAction> key_state_map_;

    std::pair<float,float> mouse_position_;

    static std::map<std::string, KeyCode> key_names_map_;

    // Clear the action map every frame, but the state
    // map should persist.
    bool update() {
        for (auto& iter : key_action_map_) {
           iter.second.clear();
        }
        return true; 
    }

};
} // display


#endif // DISPLAY_INPUT_MANAGER_HPP_
