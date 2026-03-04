//
// Created by arch-excalixy on 3/1/26.
//

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ExcalCore/Rendering/Renderer.h"

#include "ExcalCore/Objects/Components/Camera.h"
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
    _window = glfwCreateWindow(_window_size.x, _window_size.y, "ExcalEngine", nullptr, nullptr);
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
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, const int width, const int height) {
        static_cast<Renderer*>(glfwGetWindowUserPointer(window))->OnViewportSizeChange(width, height);
    });

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    _cam_data_ubo = GenerateUBO(sizeof(Cam_Data), 0);
}

void Renderer::BeginRendering(const Cam_Data& data) const {
    glClearColor(0.0f, 0.02f, 0.02f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SetUBOData(_cam_data_ubo, sizeof(Cam_Data), &data, 0);
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
    //if (!mesh_renderer) { Debug::LogError("mesh_renderer is null!"); return; }

    auto mesh_data = mesh_renderer->GetMesh();
    auto transform = mesh_renderer->GetTransform();
    auto mat_first = mesh_renderer->GetMaterial(0);

    //if (!mesh_data)  { Debug::LogError("mesh_data is null!"); return; }
    //if (!transform)  { Debug::LogError("transform is null!"); return; }
    //if (!mat_first)  { Debug::LogError("material is null!"); return; }
    //if (mat_first->GetProgram() == 0) { Debug::LogError("shader program is 0!"); return; }
    //if (mesh_data->GetVAO() == 0) { Debug::LogError("VAO is 0!"); return; }

    mesh_data->BindBuffer();
    glUseProgram(_cur_program);

    glm::mat4 model = glm::mat4(1.0f); // identity, no transform at all
    mat_first->SetUniformMat4("u_Model", model);    //glUseProgram(mat_first->GetProgram());

    //// remove BufferData from here!

    //auto model = glm::mat4(1.0f);
    //model = glm::translate(model, transform->GetPosition());
    //model *= glm::mat4(transform->GetRotation());
    //model = glm::scale(model, transform->GetScale());

    //mat_first->SetUniformMat4("u_Model", model);
    //mat_first->SetUniformMat3("u_ModelMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

    glDrawElements(GL_TRIANGLES, static_cast<int>(mesh_data->GetIndexCount()), GL_UNSIGNED_INT, 0);
    Mesh::UnbindBuffer();

    // check for GL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        Debug::LogError("GL Error after draw: {}", err);


    Debug::Log("u_Model location: {}", mat_first->GetUniformLocation("u_Model"));
    Debug::Log("u_ModelMatrix location: {}", mat_first->GetUniformLocation("u_ModelMatrix"));
}
void Renderer::InitWindow() {
}

void Renderer::FlushRendering() {
}

void Renderer::EndRendering() {
    glfwSwapBuffers(_window);
}

unsigned int Renderer::GenerateUBO(const GLsizeiptr size, const int index) {
    unsigned int ret = 0;

    glGenBuffers(1, &ret);
    glBindBuffer(GL_UNIFORM_BUFFER, ret);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, ret);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return ret;
}

void Renderer::SetUBOData(const unsigned int index, const int size, const void *data, const GLintptr offset) {
    glBindBuffer(GL_UNIFORM_BUFFER, index);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

float Renderer::GetAspectRatio() const {
    return static_cast<float>(_window_size.x) / static_cast<float>(_window_size.y);
}
