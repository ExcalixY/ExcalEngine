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

    void Run() {
        switch (_mode) {
            case RuntimeMode::EDITOR:
                RunEditor();
                return;
            case RuntimeMode::DEBUG: case RuntimeMode::RELEASE:
                RunStandalone();
                return;
        }
    }

    void SetActiveCamera(Camera* camera) { _active_camera = camera; }
    Camera* GetActiveCamera() const { return _active_camera; }

private:
    void RunStandalone();
    void RunEditor();

    RuntimeMode _mode;
    Renderer _renderer;
    Time _time;
    InputSystem _input_system;
    Camera* _active_camera;
    std::unordered_map<std::string, Shader> _compiled_shaders;
    // PhysicsSystem _physics_system;
};