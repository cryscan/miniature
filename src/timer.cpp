//
// Created by lepet on 5/12/2019.
//

#include <timer.h>

void timer::tick() {
    last = current;
    current = clock::now();
}

timer::duration timer::delta_time() {
    return current - last;
}
