//
// Created by arch-excalixy on 3/2/26.
//

#include "ExcalCore/Objects/Components/Camera.h"
#include "ExcalCore/Objects/Components/Transform.h"

const glm::mat4& Camera::GetProjectionMatrix() const {
    RecalculateProjectionMatrix();
    return _proj_matrix;
}

const glm::mat4& Camera::GetViewMatrix() const {
    RecalculateViewMatrix();
    return _view_matrix;
}

void Camera::RecalculateProjectionMatrix() const {
    _proj_matrix = glm::perspective(glm::radians(_fov), 1.0f, _near_clip, _far_clip);
}

void Camera::RecalculateViewMatrix() const {
    _view_matrix = glm::lookAt(_transform->GetPosition(), _transform->GetPosition() + _transform->Forward(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetFOV(const float fov) {
    _fov = fov;
    _is_dirty = true;
}

void Camera::SetNearClip(const float near_clip) {
    _near_clip = near_clip;
    _is_dirty = true;
}

void Camera::SetFarClip(const float far_clip) {
    _far_clip = far_clip;
    _is_dirty = true;
}