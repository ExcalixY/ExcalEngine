#pragma once

#include "ExcalCore/Rendering/Renderer.h"
#include "ExcalCore/Systems/Input/InputSystem.h"
#include "ExcalCore/Systems/Time/Time.h"
#include "ExcalCore/Objects/Components/Camera.h"

enum class RuntimeMode {
    EDITOR,
    DEBUG,
    RELEASE
};

class Runtime {
public:
    explicit Runtime(RuntimeMode mode);
    ~Runtime();

    void RunStandalone();
    void RunEditor();

    void SetActiveCamera(Camera* camera) { _active_camera = camera; }
    Camera* GetActiveCamera() const { return _active_camera; }

private:
    RuntimeMode _mode;
    Renderer _renderer;
    Time _time;
    InputSystem _input_system;
    Camera* _active_camera;
    // PhysicsSystem _physics_system;
};