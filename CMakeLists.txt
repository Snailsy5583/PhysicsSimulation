cmake_minimum_required(VERSION 3.25)
project(PhysicsSimulation)

set(CMAKE_CXX_STANDARD 17)

################
add_subdirectory(src/Engine)
add_subdirectory(src/Sandbox)
add_subdirectory(src/Physics)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)