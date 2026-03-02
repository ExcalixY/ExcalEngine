//
// Created by arch-excalixy on 3/1/26.
//

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ExcalCore/Rendering/Renderer.h"

#include "ExcalCore/Objects/GameObject.h"
#include "ExcalCore/Objects/Components/MeshRenderer.h"
#include "ExcalCore/Systems/Debug/Log.h"
#include "ExcalCore/Systems/Input/InputSystem.h"

Renderer::Renderer() {
    // Initialize GLFW
    if (!glfwInit()) {
        Debug::LogError("Failed to initialize GLFW.");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    _window = glfwCreateWindow(_window_width, _window_height, "ExcalEngine", nullptr, nullptr);
    if (!_window) {
        Debug::LogError("Failed to create GLFW window.");
        glfwTerminate();
        _running = false;
        return;
    }

    glfwMakeContextCurrent(_window);

    // Initialize GLAD - must be after MakeContextCurrent
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Debug::LogError("Failed to initialize GLAD.");
        _running = false;
        return;
    }

    // Now safe to call OpenGL functions
    glViewport(0, 0, _window_width, _window_height);

    // Callbacks
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        static_cast<Renderer*>(glfwGetWindowUserPointer(window))->OnViewportSizeChange(width, height);
    });

    glEnable(GL_DEPTH_TEST);

    _running = true;
}

void Renderer::RenderToScreen() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glfwSwapBuffers(_window);
}

void Renderer::OnViewportSizeChange(const int width, const int height) {
    _window_width = width;
    _window_height = height;
    glViewport(0, 0, width, height);
}

Renderer::~Renderer() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}