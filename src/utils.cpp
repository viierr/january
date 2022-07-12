#include "utils.hpp"

std::string utils::exec(const char* p) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(p, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

bool utils::vswhere_exists() {
    return !system("vswhere.exe > nul");
}

std::string utils::get_username() {
    return std::getenv("USERNAME");
}