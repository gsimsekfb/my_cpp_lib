#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <random>

using namespace std::filesystem;

std::vector<std::string> get_files(std::string_view path_) {
    std::vector<std::string> files;
    for (auto& entry : directory_iterator(path(path_)))
        if (entry.is_regular_file())
            files.push_back(entry.path().string());
    return files;
}

std::string random_my_rust_lib_file() {
    auto files = get_files("C:/code/my_cpp_lib/src/");
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, files.size() - 1);
    return files[dist(rng)];
}

void open_vscode(std::string_view file) {
    auto pos = file.find("code");
    std::string file_name = std::string(file.substr(pos + 4));
    std::cout << "\n-- opening file " << file_name << " ...\n";
    std::string cmd = "\"\"C:\\Users\\gokha\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\" \"" + std::string(file) + "\"\"";
    std::system(cmd.c_str());
}
