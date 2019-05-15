//
// Created by lepet on 5/14/2019.
//

#ifndef MINIATURE_COMPONENT_H
#define MINIATURE_COMPONENT_H

class component {
public:
    component() = default;
    virtual ~component() = default;

    component(const component&) = delete;
    component(component&&) = delete;
    component operator=(component&) = delete;
};


#endif //MINIATURE_COMPONENT_H
