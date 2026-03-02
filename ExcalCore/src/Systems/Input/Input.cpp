//
// Created by arch-excalixy on 3/2/26.
//

#include "ExcalCore/Systems/Input/Input.h"
#include "ExcalCore/Systems/Debug/Log.h"

#include <format>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

constexpr int KeyToIndex(const KeyCode code) {
    const int glfw_key = static_cast<int>(code);

    if (glfw_key == GLFW_KEY_UNKNOWN) {
        return 0;
    }

    if (glfw_key >= 32  && glfw_key <= 96) {
        return glfw_key - 31;        // 1  - 65
    }

    if (glfw_key >= 256 && glfw_key <= 348) {
        return glfw_key - 190;
    }

    return 0;
}

constexpr int IndexToKey(const int index) {
    if (index == 0) {
        return GLFW_KEY_UNKNOWN;
    }

    if (index >= 1   && index <= 65) {
        return index + 31;    // 32  - 96
    }

    if (index >= 66  && index <= 158) {
        return index + 190;   // 256 - 348
    }

    return GLFW_KEY_UNKNOWN; // out of range
}

Input::Input() {
    for (int i = 0; i < INPUT_KEY_CODE_COUNT; i++) {
        _key_map[i] = InputState::IDLE;
    }
}

Input::~Input() = default;

void Input::Update(GLFWwindow* window) {
    auto inst = Input::Get();

    for (int i = 0; i < INPUT_KEY_CODE_COUNT; i++) {
        auto &state = inst->_key_map[i];

        if (glfwGetKey(window, IndexToKey(i)) == GLFW_PRESS) {
            if (state == InputState::PRESSED) {
                state = InputState::HELD;
            } else {
                state = InputState::PRESSED;
            }
        } else {
            if (state == InputState::HELD) {
                state = InputState::RELEASED;
            } else if (state == InputState::RELEASED) {
                state = InputState::IDLE;
            }
        }
    }
}

bool Input::GetKeyDown(KeyCode key) {
    auto inst = Input::Get();
    return inst->_key_map[KeyToIndex(key)] == InputState::PRESSED;
}

bool Input::GetKeyUp(KeyCode key) {
    auto inst = Input::Get();
    return inst->_key_map[KeyToIndex(key)] == InputState::RELEASED;
}

bool Input::GetKey(KeyCode key) {
    auto inst = Input::Get();

    return inst->_key_map[KeyToIndex(key)] == InputState::PRESSED ||
           inst->_key_map[KeyToIndex(key)] == InputState::HELD;
}

bool Input::GetButtonDown(const std::string &button_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBindingButton>(button_id);
        return Input::GetKeyDown(bind->key);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
        return false;
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return false;
    }
}

bool Input::GetButtonUp(const std::string &button_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBindingButton>(button_id);
        return Input::GetKeyUp(bind->key);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
        return false;
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return false;
    }
}

bool Input::GetButton(const std::string &button_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBindingButton>(button_id);
        return Input::GetKey(bind->key);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
        return false;
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return false;
    }
}

float Input::GetAxis(const std::string &axis_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBindingAxis>(axis_id);
        return Input::GetAxis(bind->positive, bind->negative);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
        return false;
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return false;
    }
}

glm::vec2 Input::GetAxis2D(const std::string &axis_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBinding2D>(axis_id);
        return Input::GetAxis2D(bind->up, bind->down, bind->left, bind->right);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
        return glm::vec2(0.0f);
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return glm::vec2(0.0f);
    }
}

glm::vec3 Input::GetAxis3D(const std::string &axis_id) {
    auto inst = Input::Get();

    try {
        auto bind = inst->GetBinding<InputBinding3D>(axis_id);
        return Input::GetAxis3D(bind->up, bind->down, bind->left, bind->right, bind->up, bind->down);
    } catch (const std::bad_cast& e) {
        Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
        return glm::vec3(0.0f);
    } catch (const std::runtime_error& e) {
        Debug::LogWarning("{}", e.what());
        return glm::vec3(0.0f);
    }
}

float Input::GetAxis(KeyCode positive, KeyCode negative) {
    auto inst = Input::Get();

    float ret = 0.0f;
    if (inst->IsActive(positive)) {
        ret += 1.0f;
    }
    if (inst->IsActive(negative)) {
        ret -= 1.0f;
    }

    return ret;
}

glm::vec2 Input::GetAxis2D(KeyCode up, KeyCode down, KeyCode left, KeyCode right) {
    auto inst = Input::Get();

    auto ret = glm::vec2(0.0f);
    if (inst->IsActive(up)) {
        ret.y += 1.0f;
    }
    if (inst->IsActive(down)) {
        ret.y -= 1.0f;
    }
    if (inst->IsActive(right)) {
        ret.x += 1.0f;
    }
    if (inst->IsActive(left)) {
        ret.x -= 1.0f;
    }

    return ret;
}

glm::vec3 Input::GetAxis3D(KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back) {
    auto inst = Input::Get();

    auto ret = glm::vec3(0.0f);
    if (inst->IsActive(up)) {
        ret.y += 1.0f;
    }
    if (inst->IsActive(down)) {
        ret.y -= 1.0f;
    }
    if (inst->IsActive(right)) {
        ret.x += 1.0f;
    }
    if (inst->IsActive(left)) {
        ret.x -= 1.0f;
    }
    if (inst->IsActive(front)) {
        ret.z += 1.0f;
    }
    if (inst->IsActive(back)) {
        ret.z -= 1.0f;
    }

    return ret;
}

void Input::BindButton(const std::string &button_id, KeyCode key) {
    auto inst = Input::Get();
    inst->_binding_map.insert_or_assign(button_id, std::make_unique<InputBindingButton>(key));
}

void Input::BindAxis(const std::string &axis_id, KeyCode positive, KeyCode negative) {
    auto inst = Input::Get();
    inst->_binding_map.insert_or_assign(axis_id, std::make_unique<InputBindingAxis>(positive, negative));
}

void Input::BindAxis2D(const std::string &axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right) {
    auto inst = Input::Get();
    inst->_binding_map.insert_or_assign(axis_id, std::make_unique<InputBinding2D>(up, down, left, right));
}

void Input::BindAxis3D(const std::string &axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front,
    KeyCode back) {
    auto inst = Input::Get();
    inst->_binding_map.insert_or_assign(axis_id, std::make_unique<InputBinding3D>(up, down, left, right, front, back));
}

bool Input::IsActive(KeyCode key) const {
    auto &it = _key_map[KeyToIndex(key)];
    return (it == InputState::PRESSED || it == InputState::HELD);
}