//
// Created by lepet on 5/9/2019.
//

#include <iostream>

#include <engine.h>

engine::engine() {
    add_component<window>(std::ref(render_buffer));
}

engine& engine::get_instance() {
    static engine instance;
    return instance;
}

void engine::start() {
    auto& window_ = get_component<window>();

    std::thread render_thread([&] {
        window_.create();
        window_.render();
    });

    timer::duration accumulated_time{0};
    timer timer_;

    while (!window_.get_done()) {
        std::unique_lock<std::mutex> lock(render_buffer.mtx);
        timer_.tick();
        accumulated_time += timer_.delta_time();

        update();
        for (; accumulated_time > update_interval; accumulated_time -= update_interval)
            fixed_update();
        render();

        render_buffer.cond.wait(lock);
    }

    render_thread.join();
}

void engine::update() {

}

void engine::fixed_update() {

}

void engine::render() {

}
