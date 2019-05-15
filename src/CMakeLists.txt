include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
        main.cpp
        common.cpp
        component.cpp
        entity.cpp
        engine.cpp
        window.cpp
        shader.cpp
        renderer.cpp
        timer.cpp)

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${ASSIMP_LIBRARIES})