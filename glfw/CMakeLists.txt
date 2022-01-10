
add_library(glfw SHARED IMPORTED GLOBAL)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib-vc2019/glfw3.dll)
set_target_properties(glfw PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib-vc2019/glfw3dll.lib)
