//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <string>

class Shader {
public:
    explicit Shader(const std::string& path_vert, const std::string& path_frag);
    ~Shader();
};
