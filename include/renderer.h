//
// Created by lepet on 5/11/2019.
//

#ifndef MINIATURE_RENDERER_H
#define MINIATURE_RENDERER_H

#include <component.h>

class renderer : public component {
public:
    ~renderer() override = default;

    virtual void render() = 0;
};

class simple_renderer : public renderer {
public:
    void render() override;
};

#endif //MINIATURE_RENDERER_H
