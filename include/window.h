//
// Created by lepet on 5/9/2019.
//

#ifndef MINIATURE_WINDOW_H
#define MINIATURE_WINDOW_H

#include <GLFW/glfw3.h>

#include <string>
#include <chrono>
#include <atomic>
#include <functional>
#include <glm/glm.hpp>

#include <component.h>

template<typename T>
struct double_buffer;

class window : public component {
public:
    using command_t = std::function<void()>;

    explicit
    window(double_buffer<command_t>& command_buffer);

    void create();
    void render();
    bool get_done() const;

    int get_width() const;
    int get_height() const;

private:
    void swap_buffer();

private:
    GLFWwindow* window_{nullptr};
    std::chrono::microseconds render_interval{1000000 / 60};

    int width{1024};
    int height{768};
    std::string title{"Miniature"};

    double_buffer<command_t>& command_buffer;
    std::atomic_bool done{false};
};

#endif //MINIATURE_WINDOW_H
