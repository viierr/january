#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "termcolor.hpp"

class io {
public:
    io() = delete;
    static std::fstream create_file(const std::string& name);
    static std::string read_file(const std::string& name);
    static void create_folder(const std::string& name);
    static void create_folders(const std::vector<std::string>& name);
};