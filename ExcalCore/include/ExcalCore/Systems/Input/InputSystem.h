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

class InputSystem {
public:
    explicit InputSystem(GLFWwindow* window);
    ~InputSystem();

    void Update();

    bool GetKeyDown(KeyCode key) const;
    bool GetKeyUp(KeyCode key) const;
    bool GetKey(KeyCode key) const;

    bool GetButtonDown(const std::string& button_id);
    bool GetButtonUp(const std::string& button_id);
    bool GetButton(const std::string& button_id);

    float GetAxis(const std::string &axis_id);
    glm::vec2 GetAxis2D(const std::string &axis_id);
    glm::vec3 GetAxis3D(const std::string &axis_id);

    float GetAxis(KeyCode positive, KeyCode negative) const;
    glm::vec2 GetAxis2D(KeyCode up, KeyCode down, KeyCode left, KeyCode right) const;
    glm::vec3 GetAxis3D(KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back) const;

    void BindButton(const std::string& button_id, KeyCode key);
    void BindAxis(const std::string& axis_id, KeyCode positive, KeyCode negative);
    void BindAxis2D(const std::string& axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right);
    void BindAxis3D(const std::string& axis_id, KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back);

protected:
    template <typename T>
    T* GetBinding(const std::string& binding_id);

    bool IsActive(KeyCode key) const;

    std::array<InputState, INPUT_KEY_CODE_COUNT> _key_map;
    std::unordered_map<std::string, std::unique_ptr<InputBindingCore>> _binding_map;
    GLFWwindow * _window;
};


template<typename T>
T* InputSystem::GetBinding(const std::string& binding_id) {
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