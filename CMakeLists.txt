cmake_minimum_required(VERSION 3.10) # Or a newer version if you prefer
project(Hello CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Enable generation of compile_commands.json for clangd/IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp)