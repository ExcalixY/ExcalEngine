#pragma once

#include "GLFW/glfw3.h"

class Renderer final {
public:
    void OnViewportSizeChange(int width, int height);

    static Renderer* Get() { return _instance;}

    Renderer();
    ~Renderer();

    void Run();

protected:
    static Renderer* _instance;

    GLFWwindow* _window;
    int _window_width = 640;
    int _window_height = 360;
};
