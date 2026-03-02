//
// Created by arch-excalixy on 3/2/26.
//

#include "ExcalCore/Objects/Components/Transform.h"

void Transform::SetPosition(const glm::vec3 &pos) {
    _pos = pos;
}

void Transform::SetRotation(const glm::quat &rot) {
    _rot = rot;
}

void Transform::SetScale(const glm::vec3 &scale) {
    _scale = scale;
}

void Transform::Move(const glm::vec3 &move_vec) {
    _pos += move_vec;
}

void Transform::Move(float x, float y, float z) {
    _pos += glm::vec3(x, y, z);
}

const glm::vec3& Transform::GetEulerAngles() {
    _euler_angles = glm::degrees(glm::eulerAngles(_rot));
    return _euler_angles;
}

void Transform::Rotate(const glm::vec3& euler_angles) {
    _rot = glm::quat(glm::radians(euler_angles)) * _rot;
}

void Transform::Rotate(const float euler_x, const float euler_y, const float euler_z) {
    _rot = glm::quat(glm::radians(glm::vec3(euler_x, euler_y, euler_z))) * _rot;
}

const glm::vec3& Transform::Forward() {
    _fwd_dir = glm::normalize(_rot * glm::vec3(0.0, 0.0, -1.0));
    return _fwd_dir;
}

const glm::vec3& Transform::Right() {
    _right_dir = glm::normalize(_rot * glm::vec3(1.0, 0.0, 0.0));
    return _right_dir;
}

const glm::vec3& Transform::Up() {
    _up_dir = glm::normalize(_rot * glm::vec3(0.0, 1.0, 0.0));
    return _up_dir;
}
