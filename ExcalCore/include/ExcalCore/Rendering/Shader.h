//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <string>
#include <cstdint>

class Shader {
public:
    enum ShaderType {
        VERTEX,
        FRAGMENT,
        COMPUTE,
        GEOMETRY
    };

    Shader() = delete;

    explicit Shader(const std::string& path, ShaderType type);
    ~Shader() = default;

    [[nodiscard]] uint32_t GetShaderID() const { return _shader_id; }

private:
    uint32_t _shader_id;
};
