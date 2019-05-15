//
// Created by lepet on 5/9/2019.
//

#include <GL/glew.h>

#include <stdexcept>

#include <window.h>
#include <engine.h>

window::window(double_buffer<command_t>& command_buffer) : command_buffer{command_buffer} {}

void window::create() {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize OpenGL.");

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_)
        throw std::runtime_error("Could not create window.");
    glfwMakeContextCurrent(window_);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Could not initialize GLEW.");
}

void window::render() {
    timer timer_;

    while (!glfwWindowShouldClose(window_)) {
        timer_.tick();

        while (!command_buffer.server_buffer.empty()) {
            auto command = command_buffer.server_buffer.front();
            command_buffer.server_buffer.pop();
            command();
        }
        swap_buffer();
        timer_.tick();

        auto duration{timer_.delta_time()};
        if (duration < render_interval)
            std::this_thread::sleep_for(render_interval - duration);

        std::unique_lock<std::mutex> lock(command_buffer.mtx);
        std::swap(command_buffer.server_buffer, command_buffer.client_buffer);
        command_buffer.cond.notify_all();
    }
    done.store(true);
}

void window::swap_buffer() {
    glfwPollEvents();
    glfwSwapBuffers(window_);
}

bool window::get_done() const {
    return done.load();
}

int window::get_width() const {
    return width;
}

int window::get_height() const {
    return height;
}
