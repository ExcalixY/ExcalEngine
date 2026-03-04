//
// Created by arch-excalixy on 3/3/26.
//

#include "ExcalCore/Rendering/Shader.h"
#include "ExcalCore/Systems/Debug/Log.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"

Shader::Shader(const std::string &path, ShaderType type) {
  std::ifstream input(path);

  if (!input) {
    Debug::LogError(
        "Could not compile shader in path {} - file does not exist.", path);
    _shader_id = 0;
    return;
  }

  std::ostringstream ss;
  ss << input.rdbuf();

  std::string data = ss.str();

  const char *data_ptr = data.c_str();

  switch (type) {
  case ShaderType::VERTEX:
    _shader_id = glCreateShader(GL_VERTEX_SHADER);
    break;
  case ShaderType::FRAGMENT:
    _shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  case ShaderType::GEOMETRY:
    _shader_id = glCreateShader(GL_GEOMETRY_SHADER);
    break;
  case ShaderType::COMPUTE:
    _shader_id = glCreateShader(GL_COMPUTE_SHADER);
    break;
  }

  glShaderSource(_shader_id, 1, &data_ptr, nullptr);
  glCompileShader(_shader_id);

  int result;
  glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(_shader_id, GL_INFO_LOG_LENGTH, &length);
    char *info = static_cast<char *>(alloca(length * sizeof(char)));
    glGetShaderInfoLog(_shader_id, length, &length, info);

    Debug::LogError("Could not compile shader {}: {}", path, info);
    _shader_id = 0;
  }
}
