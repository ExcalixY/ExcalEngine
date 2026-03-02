#pragma once

#include "GLFW/glfw3.h"

class Renderer final {
public:
    void OnViewportSizeChange(int width, int height);

    Renderer();
    ~Renderer();

    void Run();

protected:
    GLFWwindow* _window;
    int _window_width = 640;
    int _window_height = 360;
    bool _running = false;
};
