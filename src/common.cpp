//
// Created by lepet on 5/10/2019.
//

#include <common.h>

std::string io::read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}
