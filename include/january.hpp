#include <fstream>
#include <tuple>
#include <optional>
#include <map>
#include "config.hpp"
#include "compilers.hpp"
#include "termcolor.hpp"

class January {
private:
    std::string m_ProjName, m_ProjPath = "";
    ProjectLang m_ProjLang;
    ProjectArch m_Arch;
    ProjectConfig m_Config;
    BuildTool m_BuildTool;
public:
    January() = delete;

    January(const std::string& proj_name, const ProjectLang& proj_lang, const ProjectArch& arch, 
            const ProjectConfig& config, const BuildTool& build_tool, const std::string& libraries = "", 
            const std::string& proj_path = "") :
            m_ProjName(proj_name), 
            m_ProjPath(proj_path), m_ProjLang(proj_lang), m_Arch(arch), 
            m_BuildTool(build_tool) { create_project(); };

    void create_project();
    void finish_creation();
};