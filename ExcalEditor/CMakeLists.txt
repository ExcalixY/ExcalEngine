project(ExcalEditor
    VERSION 0.01
    DESCRIPTION "An editor program built for my Game Engine - ExcalEngine"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EDITOR_SRC
    src/main.cpp
)

add_executable(ExcalEditor ${EDITOR_SRC})

target_include_directories(ExcalEditor PRIVATE include)
target_link_libraries(ExcalEditor PRIVATE ExcalRuntime ExcalCore imgui glfw)