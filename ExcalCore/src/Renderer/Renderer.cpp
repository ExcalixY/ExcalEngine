#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "ExcalCore/Rendering/Renderer.h"

Renderer* Renderer::_instance = nullptr;

Renderer::Renderer() {
    _instance = this;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "ExcalEngine [ERROR]: Failed to initialize GLFW." << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    _window = glfwCreateWindow(_window_width, _window_height, "ExcalEngine", nullptr, nullptr);
    if (!_window) {
        std::cerr << "ExcalEngine [ERROR]: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(_window);

    // Initialize GLAD - must be after MakeContextCurrent
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ExcalEngine [ERROR]: Failed to initialize GLAD." << std::endl;
        return;
    }

    // Now safe to call OpenGL functions
    glViewport(0, 0, _window_width, _window_height);

    // Callbacks
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        static_cast<Renderer*>(glfwGetWindowUserPointer(window))->OnViewportSizeChange(width, height);
    });
}

void Renderer::Run() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        glfwSwapBuffers(_window);
    }
}

void Renderer::OnViewportSizeChange(int width, int height) {
    _window_width = width;
    _window_height = height;
    glViewport(0, 0, width, height);
}

Renderer::~Renderer() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}