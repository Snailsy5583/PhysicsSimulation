cmake_minimum_required(VERSION 3.25)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp CirclesApp.cpp CirclesApp.h)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Engine
        Physics
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ../../vendor/glad/include
        ../../vendor/glfw/include
        ../../vendor/stb/stb
        ../
)