//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>

#include "KeyCode.h"
#include "InputBinding.h"
#include "InputState.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

constexpr int INPUT_KEY_CODE_COUNT = 159;

struct InputBindingCore;

class Input {
public:
    static void Update(GLFWwindow *window);

    static bool GetKeyDown(KeyCode key);
    static bool GetKeyUp(KeyCode key);
    static bool GetKey(KeyCode key);

    static bool GetButtonDown(const std::string& button_id);
    static bool GetButtonUp(const std::string& button_id);
    static bool GetButton(const std::string& button_id);

    static float GetAxis(const std::string &axis_id);
    static glm::vec2 GetAxis2D(const std::string &axis_id);
    static glm::vec3 GetAxis3D(const std::string &axis_id);

    static float GetAxis(KeyCode positive, KeyCode negative);
    static glm::vec2 GetAxis2D(KeyCode up, KeyCode down, KeyCode left, KeyCode right);
    static glm::vec3 GetAxis3D(KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back);

    static void BindButton(const std::string& button_id, KeyCode key);
    static void BindAxis(const std::string& axis_id, KeyCode positive, KeyCode negative);
    static void BindAxis2D(const std::string& axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right);
    static void BindAxis3D(const std::string& axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back);

protected:
    static Input* Get() {
        static Input input;
        return &input;
    }

    template <typename T>
    T* GetBinding(const std::string& binding_id);

    bool IsActive(KeyCode key) const;

    Input();
    ~Input();

    std::array<InputState, INPUT_KEY_CODE_COUNT> _key_map;
    std::unordered_map<std::string, std::unique_ptr<InputBindingCore>> _binding_map;
};

template<typename T>
T* Input::GetBinding(const std::string& binding_id) {
    const auto it_binding = _binding_map.find(binding_id);

    if (it_binding == _binding_map.end()) {
        throw std::runtime_error(std::format("Could not find Binding of ID '{}'", binding_id));
    }

    auto bind = dynamic_cast<T*>(it_binding->second.get());
    if (!bind) {
        throw std::bad_cast();
    }

    return bind;
}
