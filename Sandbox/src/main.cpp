//
// Created by arch-excalixy on 3/1/26.
//

#include "ExcalRuntime.h"

int main() {
    auto runtime = Runtime(RuntimeMode::DEBUG);
    runtime.RunStandalone();
    return 0;
}