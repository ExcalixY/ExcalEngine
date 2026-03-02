project(ExcalCore
    VERSION 0.01
    DESCRIPTION "Core Library of the whole ExcalEngine architecture"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SRC
        src/Renderer/Renderer.cpp
)

add_library(ExcalCore SHARED ${CORE_SRC} ../Libs/glad/src/glad.c)

target_link_libraries(ExcalCore PRIVATE glfw glad imgui)

target_include_directories(ExcalCore PRIVATE
    include_private
)
target_include_directories(ExcalCore PUBLIC include)

