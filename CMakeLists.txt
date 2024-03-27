cmake_minimum_required(VERSION 3.5)
project(igm_opengl)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(test test.c)
add_executable(hellotriangle hellotriangle.c)

target_include_directories(test PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(hellotriangle PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(test PRIVATE GLEW::GLEW glfw ${OPENGL_gl_LIBRARY})
target_link_libraries(hellotriangle PRIVATE GLEW::GLEW glfw ${OPENGL_gl_LIBRARY})
