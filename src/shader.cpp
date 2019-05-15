//
// Created by lepet on 5/10/2019.
//

#include <GL/glew.h>

#include <common.h>
#include <shader.h>

shader_source::shader_source(const std::string& filename, shader_type type) :
        buffer{io::read_file(filename)},
        type{type} {
    switch (type) {
        case shader_type::vertex:
            handle = glCreateShader(GL_VERTEX_SHADER);
            break;
        case shader_type::fragment:
            handle = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    compile();
}

shader_source::~shader_source() {
    glDeleteShader(handle);
}

void shader_source::compile() {
    auto src = buffer.c_str();
    glShaderSource(handle, 1, &src, nullptr);
    glCompileShader(handle);

    int status, length;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, 0);
        glGetShaderInfoLog(handle, length, nullptr, log.data());
        throw std::runtime_error(log);
    }
}

shader_type shader_source::get_type() {
    return type;
}

GLuint shader_source::get_handle() {
    return handle;
}

template<>
class bind_guard<shader_source> {
public:
    bind_guard(GLuint handle, const std::string& filename);
    ~bind_guard();

private:
    GLuint handle;
    shader_source vertex_shader, fragment_shader;
};

bind_guard<shader_source>::bind_guard(GLuint handle, const std::string& filename) :
        handle{handle},
        vertex_shader{filename + ".vert", shader_type::vertex},
        fragment_shader{filename + ".frag", shader_type::fragment} {
    glAttachShader(handle, vertex_shader.get_handle());
    glAttachShader(handle, fragment_shader.get_handle());
}

bind_guard<shader_source>::~bind_guard() {
    glDetachShader(handle, vertex_shader.get_handle());
    glDetachShader(handle, fragment_shader.get_handle());
}

shader::shader(const std::string& filename) {
    handle = glCreateProgram();
    bind_guard<shader_source> bind{handle, filename};
    link();
}

void shader::link() {
    int status, length;
    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, 0);
        glGetProgramInfoLog(handle, length, nullptr, log.data());
        throw std::runtime_error(log);
    }
}

shader::~shader() {
    glDeleteProgram(handle);
}

GLuint shader::get_handle() {
    return handle;
}

void shader::use() {
    glUseProgram(handle);
}

void shader::create_uniform(const std::string& name) {
    uniforms[name] = glGetUniformLocation(handle, name.c_str());
}

GLuint shader::get_uniform_location(const std::string& name) {
    return uniforms[name];
}

void shader::set_uniform(const std::string& name, const glm::vec3& vec) {
    use();
    auto location = get_uniform_location(name);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void shader::set_uniform(const std::string& name, const glm::vec4& vec) {
    use();
    auto location = get_uniform_location(name);
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void shader::set_uniform(const std::string& name, const glm::mat3& mat) {
    use();
    auto location = get_uniform_location(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&mat));
}

void shader::set_uniform(const std::string& name, const glm::mat4& mat) {
    use();
    auto location = get_uniform_location(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&mat));
}

void shader::set_uniform(const std::string& name, float val) {
    use();
    auto location = get_uniform_location(name);
    glUniform1f(location, val);
}

void shader::set_uniform(const std::string& name, int val) {
    use();
    auto location = get_uniform_location(name);
    glUniform1i(location, val);
}