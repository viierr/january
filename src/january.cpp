#include "january.hpp"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include "fmt/format.h"
#include "data.hpp"
//#include <boost/algorithm/string.hpp>

void January::create_project() {
    //std::string m_ProjPath = "";
    //if no project path is specified, create project @ source/repos
    m_ProjPath.empty() ? m_ProjPath = fmt::format("C:/Users/{}/source/repos/{}/", utils::get_username(), m_ProjName) : m_ProjPath = m_ProjPath + "/" + m_ProjName + "/";    

    auto compiler_path = compilers::get_cl_path(m_Arch ? "x64" : "x86");
    
    std::cout << termcolor::green << "found cl @: " << compiler_path << "\n";

    io::create_folders({m_ProjPath, m_ProjPath + ".vscode"});
    
    if (m_ProjLang == CPP) {
        io::create_folders({m_ProjPath + "src", m_ProjPath + "include"});

        std::cout << termcolor::green << "creating files...\n";

        if (m_BuildTool == CMAKE) {
            io::create_folders({m_ProjPath + "tools", m_ProjPath + "bin", m_ProjPath + "bin/Debug", m_ProjPath + "bin/Release"});
            
            auto cmake_file = io::create_file(m_ProjPath + "CMakeLists.txt");
            cmake_file << fmt::format(CmakeLists, 
                                      fmt::arg("project_name", m_ProjName), 
                                      fmt::arg("cpp_version", "17"));

            auto launch_file = io::create_file(m_ProjPath + ".vscode/launch.json");
            launch_file << fmt::format(LaunchJsonCmake, "cppvsdbg", std::string(m_ProjName).c_str());

            auto tasks_file = io::create_file(m_ProjPath + ".vscode/tasks.json");
            tasks_file << TasksJsonCmake;

            auto build_dbg_file = io::create_file(m_ProjPath + "tools/build_dbg.bat");
            build_dbg_file << fmt::format(BuildCmake, fmt::arg("build_type", "Debug"), fmt::arg("project_name", m_ProjName));

            auto build_rel_file = io::create_file(m_ProjPath + "tools/build_rel.bat");
            build_rel_file << fmt::format(BuildCmake, fmt::arg("build_type", "Release"), fmt::arg("project_name", m_ProjName));
        }
        // TODO: add support for msbuild.
        if (m_BuildTool == CUSTOM) {
            io::create_folder(m_ProjPath + "build");
            auto tasks_file = io::create_file(m_ProjPath + ".vscode/tasks.json");
            tasks_file << TasksJson;

            auto launch_file = io::create_file(m_ProjPath + ".vscode/launch.json");
            launch_file << fmt::format(LaunchJson, "cppvsdbg", std::string("build/" + m_ProjName).c_str());

            io::create_folder(m_ProjPath + "tools");
            auto builder_file = io::create_file(m_ProjPath + "tools/builder.bat");
            builder_file << fmt::format(CustomBuilder, fmt::arg("vs_path", compilers::get_vs_install_path()), fmt::arg("address_space", m_Arch ? "64" : "32"), fmt::arg("debug", m_Config ? "" : "Zi"), 
                                        fmt::arg("cpp_version", "17"), fmt::arg("library_incl", ""),fmt::arg("output_name", m_ProjName), fmt::arg("library_lib", ""));
        }

        auto cpp_propreties = io::create_file(m_ProjPath + ".vscode/c_cpp_propreties.json");
        cpp_propreties << fmt::format(CppPropretiesJson, m_Arch ? "64" : "32", fmt::arg("compiler_path", compiler_path), fmt::arg("host_arch", m_Arch ? "x64" : "x86"), fmt::arg("cpp_version", "17"));

        auto settings_file = io::create_file(m_ProjPath + ".vscode/settings.json");
        settings_file << SettingsJson;

        auto src_file = io::create_file(m_ProjPath + "src/main.cpp");
        src_file << DummyMain;

        finish_creation();
    }

    if (m_ProjLang == PYTHON) {

    }
}

void January::finish_creation() {
    std::string in;
    std::cout << termcolor::cyan << "successfully created `" << m_ProjName << "`\n";
    std::cout << "do you want to open vscode ? [y/n]: " << termcolor::reset;
    std::cin >> in;

    if (in.size() != 1) finish_creation();
    
    (in == "y") ? utils::exec(std::string("code " + m_ProjPath).c_str()) : exit(0);
}