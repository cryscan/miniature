//
// Created by lepet on 5/14/2019.
//

#ifndef MINIATURE_ENTITY_H
#define MINIATURE_ENTITY_H

#include <memory>
#include <map>
#include <vector>
#include <typeindex>
#include <type_traits>

#include <component.h>

class entity {
public:
    entity() = default;
    virtual ~entity() = default;

    template<typename T, typename ...Args>
    void add_component(const Args& ... args);

    template<typename T>
    T& get_component() const;

private:
    std::vector<std::unique_ptr<entity>> children;
    std::map<std::type_index, std::unique_ptr<component>> components;
};

template<typename T, typename... Args>
inline void entity::add_component(const Args& ... args) {
    static_assert(std::is_base_of<component, T>::value);
    auto ptr = std::make_unique<T>(args...);
    components.insert({typeid(T), std::move(ptr)});
}

template<typename T>
inline T& entity::get_component() const {
    static_assert(std::is_base_of<component, T>::value);
    return dynamic_cast<T&>(*components.at(typeid(T)));
}


#endif //MINIATURE_ENTITY_H
