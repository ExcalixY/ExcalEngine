//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "Shader.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

class Material {
public:
    [[nodiscard]] size_t GetProgram() const { return _program; }

    Material(const std::string &path_ver, const std::string &path_frag);

    [[nodiscard]] int GetUniformLocation(const std::string & name)const;

    void SetUniformMat4(const std::string& name, const glm::mat4& mat) const;
    void SetUniformMat3(const std::string& name, const glm::mat3& mat) const;

    void SetUniformVec4(const std::string& name, const glm::vec4& vec) const;
    void SetUniformVec3(const std::string& name, const glm::vec3& vec) const;
    void SetUniformVec2(const std::string& name, const glm::vec2& vec) const;

    void SetUniformFloat(const std::string& name, float val) const;
    void SetUniformInt(const std::string& name, int val) const;

    void SetUniformBool(const std::string &name, bool val) const;

private:
    Shader _shader_vert;
    Shader _shader_frag;

    uint32_t _program = 0;
    mutable std::unordered_map<std::string, int> _uniform_locations;
};
