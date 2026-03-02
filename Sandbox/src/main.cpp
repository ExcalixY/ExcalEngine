#include "ExcalRuntime.h"

int main() {
    Runtime runtime = Runtime(RuntimeMode::RELEASE);
    runtime.RunRelease();
    return 0;
}