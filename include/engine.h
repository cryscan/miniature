//
// Created by lepet on 5/9/2019.
//

#ifndef MINIATURE_ENGINE_H
#define MINIATURE_ENGINE_H

#include <common.h>
#include <entity.h>

#include <timer.h>
#include <window.h>

class engine : public entity {
public:
    engine(engine&) = delete;
    engine operator=(engine&) = delete;

    static engine& get_instance();

    void start();

    template<typename Callable>
    void push_render_buffer(Callable func);

private:
    engine();

    void update();
    void fixed_update();
    void render();

private:
    std::chrono::microseconds update_interval{1000000 / 60};
    double_buffer<window::command_t> render_buffer;
};

template<typename Callable>
inline void engine::push_render_buffer(Callable func) {
    render_buffer.client_buffer.push(func);
}

#endif //MINIATURE_ENGINE_H
