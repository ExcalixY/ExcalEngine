//
// Created by arch-excalixy on 3/2/26.
//

#include "ExcalCore/Systems/Input/InputSystem.h"
#include "ExcalCore/Systems/Debug/Log.h"

#include <format>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

constexpr int KeyToIndex(const KeyCode code) {
  const int glfw_key = static_cast<int>(code);

  if (glfw_key == GLFW_KEY_UNKNOWN) {
    return 0;
  }

  if (glfw_key >= 32 && glfw_key <= 96) {
    return glfw_key - 31; // 1  - 65
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

  if (index >= 1 && index <= 65) {
    return index + 31; // 32  - 96
  }

  if (index >= 66 && index <= 158) {
    return index + 190; // 256 - 348
  }

  return GLFW_KEY_UNKNOWN; // out of range
}

InputSystem::InputSystem(GLFWwindow *window) : _key_map(), _window(window) {
  for (int i = 0; i < INPUT_KEY_CODE_COUNT; i++) {
    _key_map[i] = InputState::IDLE;
  }
}

InputSystem::~InputSystem() = default;

void InputSystem::Update() {
  for (int i = 0; i < INPUT_KEY_CODE_COUNT; i++) {
    auto &state = _key_map[i];

    if (glfwGetKey(_window, IndexToKey(i)) == GLFW_PRESS) {
      if (state == InputState::PRESSED) {
        state = InputState::HELD;
      } else {
        state = InputState::PRESSED;
      }
    } else {
      if (state == InputState::PRESSED || state == InputState::HELD) {
        state = InputState::RELEASED;
      } else {
        state = InputState::IDLE;
      }
    }
  }
}

bool InputSystem::GetKeyDown(const KeyCode key) const {
  return _key_map[KeyToIndex(key)] == InputState::PRESSED;
}

bool InputSystem::GetKeyUp(const KeyCode key) const {
  return _key_map[KeyToIndex(key)] == InputState::RELEASED;
}

bool InputSystem::GetKey(const KeyCode key) const {
  return _key_map[KeyToIndex(key)] == InputState::PRESSED ||
         _key_map[KeyToIndex(key)] == InputState::HELD;
}

bool InputSystem::GetButtonDown(const std::string &button_id) {
  try {
    const auto bind = GetBinding<InputBindingButton>(button_id);
    return InputSystem::GetKeyDown(bind->key);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
    return false;
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return false;
  }
}

bool InputSystem::GetButtonUp(const std::string &button_id) {
  try {
    const auto bind = GetBinding<InputBindingButton>(button_id);
    return InputSystem::GetKeyUp(bind->key);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
    return false;
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return false;
  }
}

bool InputSystem::GetButton(const std::string &button_id) {
  try {
    const auto bind = GetBinding<InputBindingButton>(button_id);
    return InputSystem::GetKey(bind->key);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", button_id);
    return false;
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return false;
  }
}

float InputSystem::GetAxis(const std::string &axis_id) {
  try {
    const auto bind = GetBinding<InputBindingAxis>(axis_id);
    return InputSystem::GetAxis(bind->positive, bind->negative);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
    return false;
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return false;
  }
}

glm::vec2 InputSystem::GetAxis2D(const std::string &axis_id) {
  try {
    const auto bind = GetBinding<InputBinding2D>(axis_id);
    return InputSystem::GetAxis2D(bind->up, bind->down, bind->left,
                                  bind->right);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
    return glm::vec2(0.0f);
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return glm::vec2(0.0f);
  }
}

glm::vec3 InputSystem::GetAxis3D(const std::string &axis_id) {
  try {
    const auto bind = GetBinding<InputBinding3D>(axis_id);
    return InputSystem::GetAxis3D(bind->up, bind->down, bind->left, bind->right,
                                  bind->up, bind->down);
  } catch (const std::bad_cast &e) {
    Debug::LogWarning("Binding '{}' is not of type 'Button'", axis_id);
    return glm::vec3(0.0f);
  } catch (const std::runtime_error &e) {
    Debug::LogWarning("{}", e.what());
    return glm::vec3(0.0f);
  }
}

float InputSystem::GetAxis(const KeyCode positive,
                           const KeyCode negative) const {
  float ret = 0.0f;
  if (IsActive(positive)) {
    ret += 1.0f;
  }
  if (IsActive(negative)) {
    ret -= 1.0f;
  }

  return ret;
}

glm::vec2 InputSystem::GetAxis2D(const KeyCode up, const KeyCode down,
                                 const KeyCode left,
                                 const KeyCode right) const {
  auto ret = glm::vec2(0.0f);
  if (IsActive(up)) {
    ret.y += 1.0f;
  }
  if (IsActive(down)) {
    ret.y -= 1.0f;
  }
  if (IsActive(right)) {
    ret.x += 1.0f;
  }
  if (IsActive(left)) {
    ret.x -= 1.0f;
  }

  return ret;
}

glm::vec3 InputSystem::GetAxis3D(const KeyCode up, const KeyCode down,
                                 const KeyCode left, const KeyCode right,
                                 const KeyCode front,
                                 const KeyCode back) const {

  auto ret = glm::vec3(0.0f);
  if (IsActive(up)) {
    ret.y += 1.0f;
  }
  if (IsActive(down)) {
    ret.y -= 1.0f;
  }
  if (IsActive(right)) {
    ret.x += 1.0f;
  }
  if (IsActive(left)) {
    ret.x -= 1.0f;
  }
  if (IsActive(front)) {
    ret.z += 1.0f;
  }
  if (IsActive(back)) {
    ret.z -= 1.0f;
  }

  return ret;
}

void InputSystem::BindButton(const std::string &button_id, KeyCode key) {
  _binding_map.insert_or_assign(button_id,
                                std::make_unique<InputBindingButton>(key));
}

void InputSystem::BindAxis(const std::string &axis_id, KeyCode positive,
                           KeyCode negative) {
  _binding_map.insert_or_assign(
      axis_id, std::make_unique<InputBindingAxis>(positive, negative));
}

void InputSystem::BindAxis2D(const std::string &axis_id, KeyCode up,
                             KeyCode down, KeyCode left, KeyCode right) {
  _binding_map.insert_or_assign(
      axis_id, std::make_unique<InputBinding2D>(up, down, left, right));
}

void InputSystem::BindAxis3D(const std::string &axis_id, KeyCode up,
                             KeyCode down, KeyCode left, KeyCode right,
                             KeyCode front, KeyCode back) {
  _binding_map.insert_or_assign(
      axis_id,
      std::make_unique<InputBinding3D>(up, down, left, right, front, back));
}

bool InputSystem::IsActive(const KeyCode key) const {
  const auto &it = _key_map[KeyToIndex(key)];
  return it == InputState::PRESSED || it == InputState::HELD;
}
