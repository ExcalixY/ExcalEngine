//
// Created by arch-excalixy on 3/1/26.
//

#include "ExcalRuntime/Runtime.h"
#include "ExcalCore/Objects/GameObject.h"

Runtime::Runtime(const RuntimeMode mode) :
    _mode(mode), _renderer(Renderer()), _time(Time()), _input_system(_renderer.GetWindow()) {}

Runtime::~Runtime() = default;

void Runtime::RunStandalone() {
    bool _running = true;

    GameObject obj = GameObject();
    auto cam = obj.AddComponent<Camera>();

    cam->SetFOV(90.0f);
    cam->SetNearClip(0.01f);
    cam->SetFarClip(0.01f);

    SetActiveCamera(cam);

    GameObject obj_2 = GameObject();
    auto trans = obj_2.GetComponent<Transform>();

    while (_running) {
        glfwPollEvents();
        _input_system.Update();
        _time.Update();

        if (_input_system.GetKeyDown(KeyCode::Escape) || glfwWindowShouldClose(_renderer.GetWindow())) {
            _running = false;
        }

        _renderer.RenderToScreen();
    }
}

void Runtime::RunEditor() {}