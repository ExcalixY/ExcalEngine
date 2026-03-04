//
// Created by arch-excalixy on 3/1/26.
//

#include "glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "ExcalCore/Rendering/Renderer.h"

#include "ExcalCore/Objects/Components/Camera.h"
#include "ExcalCore/Objects/Components/Transform.h"
#include "ExcalCore/Rendering/GPU_Data.h"
#include "ExcalCore/Systems/Debug/Log.h"
#include "ExcalCore/Systems/Input/InputSystem.h"

#include "glm/gtc/type_ptr.hpp"

Renderer::Renderer() {
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

  // Initialize GLFW
  if (!glfwInit()) {
    Debug::LogError("Failed to initialize GLFW.");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  _window = glfwCreateWindow(_window_size.x, _window_size.y, "ExcalEngine",
                             nullptr, nullptr);
  if (!_window) {
    Debug::LogError("Failed to create GLFW window.");
    glfwTerminate();
    _running = false;
    return;
  }

  glfwMakeContextCurrent(_window);

  // Initialize GLAD - must be after MakeContextCurrent
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    Debug::LogError("Failed to initialize GLAD.");
    _running = false;
    return;
  }

  // Now safe to call OpenGL functions
  glViewport(0, 0, _window_size.x, _window_size.y);

  // Callbacks
  glfwSetWindowUserPointer(_window, this);
  glfwSetFramebufferSizeCallback(
      _window, [](GLFWwindow *window, const int width, const int height) {
        static_cast<Renderer *>(glfwGetWindowUserPointer(window))
            ->OnViewportSizeChange(width, height);
      });

  glEnable(GL_DEPTH_TEST);

  _cam_data_ubo = GenerateUBO(sizeof(Cam_Data), 0);
}

void Renderer::BeginRendering(Camera *active_cam) {
  glClearColor(0.0f, 0.02f, 0.02f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _active_cam = active_cam;
}

void Renderer::OnViewportSizeChange(const int width, const int height) {
  _window_size.x = width;
  _window_size.y = height;
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Renderer::RenderMesh(MeshRenderer *mesh_renderer) const {
  auto mesh_data = mesh_renderer->GetMesh();
  auto transform = mesh_renderer->GetTransform();
  auto mat_first = mesh_renderer->GetMaterial(0);

  glUseProgram(mat_first->GetProgram());
  mesh_data->BindBuffer();

  transform->Move(0.01f, 0, 0);

  mat_first->SetUniformMat4("u_Model", mesh_renderer->_model_matrix);
  mat_first->SetUniformMat4("u_Projection", _active_cam->GetProjectionMatrix());
  mat_first->SetUniformMat4("u_View", _active_cam->GetViewMatrix());

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  Mesh::UnbindBuffer();

  // check for GL errors
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
    Debug::LogError("GL Error after draw: {}", err);
}
void Renderer::InitWindow() {}

void Renderer::FlushRendering() {}

void Renderer::EndRendering() { glfwSwapBuffers(_window); }

unsigned int Renderer::GenerateUBO(const GLsizeiptr size, const int index) {
  unsigned int ret = 0;

  glGenBuffers(1, &ret);
  glBindBuffer(GL_UNIFORM_BUFFER, ret);
  glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, index, ret);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  return ret;
}

void Renderer::SetUBOData(const unsigned int index, const int size,
                          const void *data, const GLintptr offset) {
  glBindBuffer(GL_UNIFORM_BUFFER, index);
  glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

float Renderer::GetAspectRatio() const {
  return static_cast<float>(_window_size.x) /
         static_cast<float>(_window_size.y);
}
