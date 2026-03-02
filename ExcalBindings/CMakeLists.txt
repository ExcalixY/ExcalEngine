project(ExcalBindings
    VERSION 0.01
    DESCRIPTION "A Scripting Binding List built for my Game Engine - ExcalEngine"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EDITOR_SRC
        src/main.cpp
)

add_executable(ExcalBindings ${EDITOR_SRC})

target_include_directories(ExcalBindings PRIVATE include)
target_link_libraries(ExcalBindings PRIVATE ExcalCore)