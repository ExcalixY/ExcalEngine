//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "GLFW/glfw3.h"

class Time {
public:
    explicit Time() = default;

    void Update() {
        const auto cur_time = glfwGetTime();

        _delta_time_unscaled = cur_time - _last_frame_time;
        _time_unscaled += _delta_time_unscaled;

        _delta_time = _delta_time_unscaled * _time_scale;
        _time += _delta_time;

        _last_frame_time = cur_time;
    }

    void SetTimeScale(const double scale) {
        _time_scale = scale;
    }

    [[nodiscard]] const double& DeltaTime() const { return _delta_time; }
    [[nodiscard]] const double& TimeScale() const { return _time_scale; }
    [[nodiscard]] const double& DeltaTimeUnscaled() const { return _delta_time_unscaled; }

private:
    double _delta_time = 0.0;
    double _time = 0.0;
    double _time_unscaled = 0.0;
    double _delta_time_unscaled = 0.0;
    double _time_scale = 1.0;
    double _last_frame_time = 0.0;
};
