#pragma once
#include <map>
#include <string>
#include <optional>

template<typename T>
class resolver {
    std::map<std::string, T> emap = {};
public:
    resolver() {}
    std::optional<T> find(const std::string& key) {
        for (const auto& [k, v] : emap) {
            if (k == key) return v;
        }
        return std::nullopt;
    }
};

enum ErrorCode {
    FILE_ALREADY_EXISTS,
    FOLDER_ALREADY_EXISTS,
    OK
    /* ... */
};

enum ProjectLang {
    CPP,
    PYTHON
    /* ... */
};

resolver<ProjectLang>::resolver() {
    emap = {
        {"PROJ_CPP", CPP},
        {"PROJ_PYTHON", PYTHON}
    };
}

enum ProjectArch {
    X86,
    X64
    /* ... */
};

resolver<ProjectArch>::resolver() {
    emap = {
        {"x86", X86},
        {"x64", X64}
    };
}

enum ProjectConfig {
    DEBUG,
    RELEASE
};

resolver<ProjectConfig>::resolver() {
    emap = {
        {"DEBUG", DEBUG},
        {"RELEASE", RELEASE}
    };
}

enum BuildTool {
    CMAKE,
    //VS,
    CUSTOM
};

resolver<BuildTool>::resolver() {
    emap = {
        {"CMAKE", CMAKE},
        {"CUSTOM", CUSTOM}
    };
}

enum LibType {
    DYNAMIC,
    STATIC
};

resolver<LibType>::resolver() {
    emap = {
        {"DYNAMIC", DYNAMIC},
        {"STATIC", STATIC}
    };
}

enum BinaryType {
    EXECUTABLE,
    LIBRARY,
    DLL
};

resolver<BinaryType>::resolver() {
        emap = {
        {"EXECUTABLE", EXECUTABLE},
        {"LIBRARY", LIBRARY},
        {"DLL", DLL}
    };
}
