//
// Created by arch-excalixy on 3/3/26.
//

#pragma once

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

constexpr int MAX_LIGHT_COUNT = 16;

struct alignas(16) LightInstance_Data {
    glm::vec3 pos;
    int type; // 0 - directional, 1 - point, 2 - spot
    glm::vec4 color_intensity;
    glm::vec3 dir;
    int cast_shadow;
};

struct alignas(16) LightMap_Data {
    LightInstance_Data lights[MAX_LIGHT_COUNT];
    LightInstance_Data dir_light;

    glm::vec3 ambient_color;
    unsigned int light_count;
};

struct alignas(16) Cam_Data {
    glm::mat4 proj_view;

    glm::mat4 proj;
    glm::mat4 view;

    glm::vec3 cam_pos;
    float near_clip;
    glm::vec3 cam_dir;
    float far_clip;
};