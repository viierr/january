#pragma once
#include <string>
#include <iostream>

class utils {
public:
    utils() = delete;
    static std::string exec(const char* p);
    static bool vswhere_exists();
    static std::string get_username();
};