//
// Created by lepet on 5/12/2019.
//

#ifndef MINIATURE_TIMER_H
#define MINIATURE_TIMER_H

#include <chrono>

class timer {
public:
    using clock = std::chrono::high_resolution_clock;
    using duration = clock::duration;
    using time_point = clock::time_point;

    void tick();
    duration delta_time();

private:
    time_point last{clock::now()};
    time_point current{clock::now()};
};

#endif //MINIATURE_TIMER_H
