//
// Created by arch-excalixy on 3/3/26.
//

#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex(const glm::vec3 pos, const glm::vec3 normal, const glm::vec2 uv) : pos(pos), normal(normal), uv(uv) {}
    Vertex() : pos(glm::vec3(0.0f)), normal(glm::vec3(0)), uv(glm::vec2(0.0f)) {}
};