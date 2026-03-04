project(ExcalCore
    VERSION 0.01
    DESCRIPTION "Core Library of the whole ExcalEngine architecture"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SRC
        src/Renderer/Renderer.cpp
        src/Systems/Input/InputSystem.cpp
        src/Objects/Components/Camera.cpp
        src/Core/UUID/UUID_Manager.cpp
        src/Objects/Components/Transform.cpp
        src/Renderer/Meshes/Mesh.cpp
        include/ExcalCore/Rendering/GPU_Data.h
        src/Renderer/Material.cpp
        src/Renderer/Shader.cpp
)

add_library(ExcalCore SHARED ${CORE_SRC} ../Libs/glad/src/glad.c)

target_link_libraries(ExcalCore PUBLIC glfw imgui glm)
target_link_libraries(ExcalCore PRIVATE glad)

target_include_directories(ExcalCore PRIVATE include_private)
target_include_directories(ExcalCore PUBLIC include)

