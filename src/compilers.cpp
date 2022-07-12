#include "compilers.hpp"

std::string compilers::get_vs_install_path() {
    auto vs_install_path = utils::exec("vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath");

    if (vs_install_path.empty()) {
        std::cout << termcolor::yellow << __FILE__ << ": visual studio does not exist or VC Tools are not installed, please check your visual studio installation. aborting.\n";
        exit(EXIT_FAILURE);
    }

    vs_install_path.resize(vs_install_path.size() - 1);
    std::replace(vs_install_path.begin(), vs_install_path.end(), '\\', '/');

    return vs_install_path;
}

std::string compilers::get_cl_path(const std::string& arch) {
    if (!utils::vswhere_exists()) {
        std::cout << termcolor::yellow << __FILE__ << ": vswhere not found, make sure visual studio is installed or if the install is not corrumpted. aborting.\n";
        exit(EXIT_FAILURE);
    }

    auto vs_install_dir = get_vs_install_path();

    auto vct_ver = io::read_file(vs_install_dir + "/VC/Auxiliary/Build/Microsoft.VCToolsVersion.default.txt");
    vct_ver.resize(vct_ver.size() - 1);

    std::cout << termcolor::green << __FILE__ << ": vc tools version: " << vct_ver << "\n";
    auto cl_path = vs_install_dir + "/VC/Tools/MSVC/" + vct_ver + "/bin/Host" + arch + "/" + arch + "/cl.exe";

    return cl_path;
}