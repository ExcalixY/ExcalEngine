//
// Created by arch-excalixy on 3/1/26.
//

#include "ExcalRuntime.h"

int main() {
  auto runtime = Runtime(RuntimeMode::RELEASE);
  runtime.Run();
  return 0;
}
