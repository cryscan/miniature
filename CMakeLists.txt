cmake_minimum_required(VERSION 3.14)
project(miniature)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cmake-build-debug)

find_package(OPENGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(BOOST REQUIRED)
find_package(GLM REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${ASSIMP_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR})

add_subdirectory(src)