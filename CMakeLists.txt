cmake_minimum_required(VERSION 3.10)
project(ExcalEngineWorkspace
    VERSION 0.01
    DESCRIPTION "ExcalEngine - Yet another terrible C++ Game Engine."
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

option(EXCALENGINE_BUILD_EDITOR "Build Editor" ON)

if(WIN32)
    message("ExcalEngine Build - Platform: Windows")
    add_compile_definitions(EXCALENGINE_WINDOWS)
elseif(UNIX AND NOT APPLE OR LINUX)
    message("ExcalEngine Build - Platform: Linux")
    add_compile_definitions(EXCALENGINE_LINUX)
elseif (UNIX AND APPLE)
    message("ExcalEngine Build - Platform: MacOS")
    add_compile_definitions(EXCALENGINE_LINUX)
else()
    message("ExcalEngine Build - Platform: Unsupported.")
    message("ExcalEngine Build - Stopping building. Please wait for added support for your specific environment or add a compile flag [WIN32, LINUX, UNIX APPLE]")
    return(0)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(EXCALENGINE_DEBUG)
    message("ExcalEngine Build - Build Type: DEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(EXCALENGINE_RELEASE)
    message("ExcalEngine Build - Build Type: RELEASE")
endif()

# Libraries
add_subdirectory(Libs/glfw)
add_subdirectory(Libs/imgui)

add_library(glad STATIC Libs/glad/src/glad.c)
target_include_directories(glad PUBLIC Libs/glad/include)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE Libs/glm)

# Engine
add_subdirectory(ExcalCore)
# add_subdirectory(ExcalBindings)
# add_subdirectory(ExcalCSharp)
add_subdirectory(ExcalRuntime)
if (EXCALENGINE_BUILD_EDITOR)
    add_compile_definitions(EXCALENGINE_EDITOR)
    add_subdirectory(ExcalEditor)
endif()

# Test Game
add_subdirectory(Sandbox)