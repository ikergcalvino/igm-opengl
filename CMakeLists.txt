cmake_minimum_required(VERSION 3.5)
project(igm_opengl)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(spinningcube spinningcube.cpp)

target_include_directories(spinningcube PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(spinningcube PRIVATE GLEW::GLEW glfw ${OPENGL_gl_LIBRARY})
