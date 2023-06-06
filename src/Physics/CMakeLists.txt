cmake_minimum_required(VERSION 3.25)
project(Physics)

set(CMAKE_CXX_STANDARD 17)

set(__solver
        PhysicsComponent.cpp
        PhysicsComponent.h
)

add_library(${PROJECT_NAME} ${__solver})

target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw
        ImGui
        Engine
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ../../vendor/glad/include
        ../../vendor/glfw/include
        ../../vendor/stb/stb
        ../
)