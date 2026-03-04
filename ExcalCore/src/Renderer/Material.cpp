//
// Created by arch-excalixy on 3/3/26.
//

#include "ExcalCore/Rendering/Material.h"

#include "ExcalCore/Systems/Debug/Log.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

Material::Material(const std::string& path_ver, const std::string& path_frag) :
    _shader_vert(path_ver, Shader::VERTEX), _shader_frag(path_frag, Shader::FRAGMENT) {
    if (_shader_vert.GetShaderID() == 0) {
        Debug::LogError("Vertex shader failed to compile, cannot link!");
        return;
    }
    if (_shader_frag.GetShaderID() == 0) {
        Debug::LogError("Fragment shader failed to compile, cannot link!");
        return;
    }

    _program = glCreateProgram();
    glAttachShader(_program, _shader_vert.GetShaderID());
    glAttachShader(_program, _shader_frag.GetShaderID());

    glLinkProgram(_program);
    glValidateProgram(_program);

    glDetachShader(_program, _shader_vert.GetShaderID());
    glDetachShader(_program, _shader_frag.GetShaderID());
}

void Material::SetUniformMat4(const std::string &name, const glm::mat4 &mat) const {
    glProgramUniformMatrix4fv(_program, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Material::SetUniformMat3(const std::string &name, const glm::mat3 &mat) const {
    glProgramUniformMatrix3fv(_program, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

auto Material::SetUniformVec4(const std::string &name, const glm::vec4 &vec) const -> void {
    glProgramUniform4fv(_program, GetUniformLocation(name), 1, &vec[0]);
}

void Material::SetUniformVec3(const std::string &name, const glm::vec3 &vec) const {
    glProgramUniform3fv(_program, GetUniformLocation(name), 1, &vec[0]);
}

void Material::SetUniformVec2(const std::string &name, const glm::vec2 &vec) const {
    glProgramUniform2fv(_program, GetUniformLocation(name), 1, &vec[0]);
}

void Material::SetUniformFloat(const std::string &name, float val) const {
    glProgramUniform1f(_program, GetUniformLocation(name), val);
}

void Material::SetUniformInt(const std::string &name, int val) const {
    glProgramUniform1i(_program, GetUniformLocation(name), val);
}

void Material::SetUniformBool(const std::string &name, bool val) const {
    glProgramUniform1i(_program, GetUniformLocation(name), val);
}

int Material::GetUniformLocation(const std::string &name) const {
    auto it = _uniform_locations.find(name);

    if (it != _uniform_locations.end()) {
        return it->second;
    }

    const int loc = glGetUniformLocation(_program, name.c_str());
    _uniform_locations[name] = loc;
    return loc;
}
