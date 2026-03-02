#pragma once

#include "ExcalCore/Rendering/Renderer.h"

#include <memory>

enum class RuntimeMode {
    EDITOR,
    DEBUG_STANDALONE,
    RELEASE
};

class Runtime {
public:
    explicit Runtime(RuntimeMode mode);
    ~Runtime();

    void RunRelease();
    void RunDebugStandalone();
    void RunEditor();

private:
    RuntimeMode _mode;
    Renderer _renderer;
    // PhysicsSystem _physics_system;
};