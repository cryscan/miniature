//
// Created by lepet on 5/10/2019.
//

#ifndef MINIATURE_SHADER_H
#define MINIATURE_SHADER_H

#include <string>
#include <map>
#include <glm/glm.hpp>

enum class shader_type {
    vertex, fragment
};

class shader_source {
public:
    shader_source(const std::string& filename, shader_type type);
    ~shader_source();

    shader_type get_type();
    GLuint get_handle();

private:
    void compile();

private:
    const std::string buffer;
    const shader_type type;
    GLuint handle;
};

class shader {
public:
    explicit shader(const std::string& filename);
    ~shader();

    GLuint get_handle();

    void use();
    void create_uniform(const std::string& name);
    GLuint get_uniform_location(const std::string& name);

    void set_uniform(const std::string& name, const glm::vec3& vec);
    void set_uniform(const std::string& name, const glm::vec4& vec);
    void set_uniform(const std::string& name, const glm::mat3& mat);
    void set_uniform(const std::string& name, const glm::mat4& mat);
    void set_uniform(const std::string& name, float val);
    void set_uniform(const std::string& name, int val);

private:
    void link();

private:
    GLuint handle;
    std::map<std::string, GLuint> uniforms;
};

#endif //MINIATURE_SHADER_H
