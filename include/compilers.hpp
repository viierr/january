#pragma once
#include <string>
#include "utils.hpp"
#include "io.hpp"
#include "config.hpp"
#include "termcolor.hpp"

class compilers {
public:
    compilers() = delete;
    static std::string get_cl_path(const std::string& arch);
    static std::string get_vs_install_path();
};