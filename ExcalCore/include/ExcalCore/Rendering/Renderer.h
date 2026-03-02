//
// Created by arch-excalixy on 3/1/26.
//

#pragma once

#include "GLFW/glfw3.h"

class Renderer final {
public:
    explicit Renderer();
    ~Renderer();

    void RenderToScreen() const;
    void OnViewportSizeChange(int width, int height);

    [[nodiscard]] GLFWwindow* GetWindow() const { return _window; }

protected:
    GLFWwindow* _window;
    int _window_width = 640;
    int _window_height = 360;
    bool _running = false;
};