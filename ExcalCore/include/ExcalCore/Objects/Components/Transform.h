//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "Component.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"

class Transform final : public Component {
public:
  explicit Transform(GameObject *const game_object)
      : Component(game_object, this) {}

  [[nodiscard]] const glm::vec3 &GetPosition() const { return _pos; }
  [[nodiscard]] const glm::quat &GetRotation() const { return _rot; }
  [[nodiscard]] const glm::vec3 &GetScale() const { return _scale; }

  void SetPosition(const glm::vec3 &pos);
  void SetRotation(const glm::quat &rot);
  void SetScale(const glm::vec3 &scale);

  void Move(const glm::vec3 &move_vec);
  void Move(float x, float y, float z);

  void Rotate(const glm::vec3 &euler_angles);
  void Rotate(float euler_x, float euler_y, float euler_z);

  [[nodiscard]] const glm::vec3 &GetEulerAngles();

  const glm::vec3 &Forward();
  const glm::vec3 &Right();
  const glm::vec3 &Up();

private:
  glm::vec3 _pos{};
  glm::quat _rot{};
  glm::vec3 _scale = glm::vec3(1, 1, 1);

  glm::vec3 _fwd_dir{};
  glm::vec3 _right_dir{};
  glm::vec3 _up_dir{};

  glm::vec3 _euler_angles{};
};
