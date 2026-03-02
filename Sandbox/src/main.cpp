//
// Created by arch-excalixy on 3/1/26.
//

#include "ExcalRuntime.h"

int main() {
    Runtime runtime = Runtime(RuntimeMode::RELEASE);
    runtime.RunRelease();
    return 0;
}