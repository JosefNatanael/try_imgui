set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

set(LINUX_GL_LIBS -lGL)
set(GLFW_STATIC_LIBS -lglfw -lrt -lm -ldl)

# add_library(imgui_lib ${IMGUI_SOURCES} ${BACKEND_SOURCES})
# target_link_libraries(imgui_lib ${LINUX_GL_LIBS} ${GLFW_STATIC_LIBS})

add_executable(try_imgui main.cpp ${IMGUI_SOURCES})
target_link_libraries(try_imgui ${LINUX_GL_LIBS} ${GLFW_STATIC_LIBS})
target_include_directories(try_imgui PRIVATE ${CMAKE_SOURCE_DIR}/imgui)
target_include_directories(try_imgui PRIVATE ${CMAKE_SOURCE_DIR}/backends)

add_executable(basic basic.cpp Application.cpp ${IMGUI_SOURCES})
target_link_libraries(basic ${LINUX_GL_LIBS} ${GLFW_STATIC_LIBS})
target_include_directories(basic PRIVATE ${CMAKE_SOURCE_DIR}/imgui)
target_include_directories(basic PRIVATE ${CMAKE_SOURCE_DIR}/backends)
