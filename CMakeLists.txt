cmake_minimum_required(VERSION 3.22)
project(test)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

find_package(Boost REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)

#
add_executable(test main.cc)
target_link_libraries(test PRIVATE glad glfw glm)
target_link_libraries(test PRIVATE Boost::boost PNG::PNG JPEG::JPEG)

add_custom_command(TARGET test POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/glfw/lib-vc2019/glfw3.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)

# file(COPY ${CMAKE_SOURCE_DIR}/glfw/lib-vc2019/glfw3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# add_dependencies(test cpdll)
# add_custom_target(cpdll COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/glfw/lib-vc2019/glfw3.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)

#
add_executable(proj proj.cc)
target_link_libraries(proj PRIVATE glm)

#
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test)