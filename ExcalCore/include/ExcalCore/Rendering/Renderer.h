//
// Created by arch-excalixy on 3/1/26.
//

#pragma once

#include "ExcalCore/Objects/Components/Camera.h"
#include "ExcalCore/Objects/Components/MeshRenderer.h"
#include "GPU_Data.h"

#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

class Renderer final {
public:
  explicit Renderer();
  ~Renderer();

  void BeginRendering(Camera *cam);
  void RenderMesh(MeshRenderer *mesh_renderer) const;
  void InitWindow();
  void OnViewportSizeChange(int width, int height);
  void SetCurrentProgram(const unsigned int program) { _cur_program = program; }

  static unsigned int GenerateUBO(GLsizeiptr size, int index);
  static void SetUBOData(unsigned int index, int size, const void *data,
                         GLintptr offset = NULL);

  [[nodiscard]] float GetAspectRatio() const;

  [[nodiscard]] GLFWwindow *GetWindow() const { return _window; }

  void FlushRendering();
  void EndRendering();

protected:
  GLFWwindow *_window;

  glm::ivec2 _window_size = glm::vec2(600, 800);
  bool _running = false;
  unsigned int _cur_program = 0;
  unsigned int _cam_data_ubo = 0;
  Camera *_active_cam = nullptr;
};
