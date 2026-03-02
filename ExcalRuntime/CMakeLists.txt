project(ExcalRuntime
    VERSION 0.01
    DESCRIPTION "A Runtime Library for my Game Engine Stack ExcalEngine"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RUNTIME_SRC
    src/Runtime.cpp
)

add_library(ExcalRuntime SHARED ${RUNTIME_SRC})

target_link_libraries(ExcalRuntime PRIVATE ExcalCore)
target_include_directories(ExcalRuntime PUBLIC include)