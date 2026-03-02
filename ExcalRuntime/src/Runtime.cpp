#include "ExcalRuntime/Runtime.h"

Runtime::Runtime(const RuntimeMode mode) : _mode(mode), _renderer() {
}

Runtime::~Runtime() {
}

void Runtime::RunRelease() {
    _renderer.Run();
}

void Runtime::RunDebugStandalone() {
}

void Runtime::RunEditor() {
}