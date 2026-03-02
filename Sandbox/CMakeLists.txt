project(CodeCard
    VERSION 0.1
    DESCRIPTION "A Sample Game for my Game Engine - ExcalEngine"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_SRC
    src/main.cpp
)

add_executable(CodeCard ${GAME_SRC})

target_link_libraries(CodeCard PRIVATE ExcalCore ExcalRuntime)