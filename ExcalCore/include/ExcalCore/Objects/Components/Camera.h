//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "Component.h"

#include "glm/mat4x4.hpp"

class Camera final : public Component {
public:
    explicit Camera(GameObject* const game_object, Transform* const transform) : Component(game_object, transform) {}

    enum class ProjectionType {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetViewMatrix() const;

    void SetProjectionType(const ProjectionType type) { _proj_type = type; }

    void SetFOV(float fov);
    void SetNearClip(float near_clip);
    void SetFarClip(float far_clip);

private:
    ProjectionType _proj_type = ProjectionType::PERSPECTIVE;
    float _fov = 0.0f;
    float _near_clip = 0.0f;
    float _far_clip = 0.0f;

    mutable glm::mat4 _proj_matrix{};
    mutable glm::mat4 _view_matrix{};

    mutable bool _is_dirty = true;

    void RecalculateProjectionMatrix() const;
    void RecalculateViewMatrix() const;
};