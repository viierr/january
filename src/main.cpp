#include <iostream>
#include <algorithm>
#include <string>
#include "fire.hpp"
#include "january.hpp"

inline std::string& to_upper(std::string& target) {
    //TODO: rethink this?
    std::transform(target.begin(), target.end(), target.begin(), ::toupper);
    return target;
}

int fired_main(
    std::string proj_name = fire::arg({"-n", "--name", "[Requiered] Define project name"}),
    std::string proj_path = fire::arg({"-p", "--path", "[Optional] Define project path"}, ""),
    std::string proj_lang = fire::arg({"-l", "--language", "[Required] Defines project lang (PYTHON/CPP for now)"}),
    std::string proj_arch = fire::arg({"-a", "--arch", "[Optional] Defines project arch, defaults to x86"}, "x86"),
    std::string proj_config = fire::arg({"-c", "--config", "[Optional] Defines project config (DEBUG/RELEASE), defaults to DEBUG"}, "DEBUG"),
    std::string proj_build_tool = fire::arg({"-b", "--build-tool", "[Optional] Defines project build tool (CMAKE/CUSTOM), defaults to CUSTOM"}, "CMAKE"),
    std::string proj_libs = fire::arg({"-v", "--vcpkg-libraries", "[Optional] Defines vcpkg installed libraries to be linked. Example usage: -t=fmt,zlib"}, "")
) 
{
    resolver<ProjectLang> c_Lang;
    resolver<ProjectArch> c_Arch;
    resolver<ProjectConfig> c_Config;
    resolver<BuildTool> c_BuildTool;

    //std::cin.get();
    January::January(proj_name, *c_Lang.find(to_upper(proj_lang)), *c_Arch.find(to_upper(proj_arch)), 
                    *c_Config.find(to_upper(proj_config)), *c_BuildTool.find(to_upper(proj_build_tool)), proj_path);
    std::cin.get();
    return 0;
}

FIRE(fired_main)