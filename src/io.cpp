#include "io.hpp"

std::fstream io::create_file(const std::string& name) {
    try {
        if (std::filesystem::exists(name)) {
            std::cout << termcolor::yellow << "file `" << name << "` already exists! aborting.\n";
            exit(EXIT_FAILURE);
        }
        auto ret = std::fstream(name, std::fstream::in |  std::fstream::out |  std::fstream::trunc);
        return ret;
    }

    catch(const std::exception& e) {
        std::cout << termcolor::red << __FILE__ << ": exception occured! " << e.what();
    }
}

std::string io::read_file(const std::string& name) {
    return std::string(std::istreambuf_iterator<char>{std::ifstream(name)}, {});
}

void io::create_folder(const std::string& name) {
    try {
        if (std::filesystem::exists(name)) {
            std::cout << termcolor::yellow << "folder `" << name << "` already exists! aborting.\n";
            exit(EXIT_FAILURE);
        }
        std::filesystem::create_directory(name);
    }
    catch (const std::exception& e) {
        std::cout << termcolor::red << __FILE__ << ": exception occured! " << e.what();
    }
}

void io::create_folders(const std::vector<std::string>& name) {
    for (const auto& n : name) {
        create_folder(n);
    }
}