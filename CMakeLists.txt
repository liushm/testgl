cmake_minimum_required(VERSION 3.22)
project(test)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(test main.cc)
target_link_libraries(test PRIVATE glad)
target_link_libraries(test PRIVATE glfw)
target_link_libraries(test PRIVATE glm)

file(COPY ${CMAKE_SOURCE_DIR}/glfw/lib-vc2019/glfw3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

