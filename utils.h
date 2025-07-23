#include <iostream>

///
template<typename T>
T&& println_impl(const char* expr, T&& value, const char* file = __FILE__, int line = __LINE__) {
    std::cerr << value << std::endl;
    return std::forward<T>(value);
}

#define println(x) println_impl(#x, x)


///
template<typename T>
T&& debug_print(const char* expr, T&& value, const char* file = __FILE__, int line = __LINE__) {
    std::cerr << "[" << file << ":" << line << "] " << expr << " = " << value << std::endl;
    return std::forward<T>(value);
}

#define dbg(x) debug_print(#x, x)


///
#define print_vec(vec) print_vec_(vec, #vec)

void print_vec_(const std::vector<int>& vec, const std::string& name) {
    std::cout << name << ": ";
    for (int e : vec) std::cout << e << " ";
    std::cout << std::endl;
}


/// cpp version
/// Note: works with this usage: cl /Zc:__cplusplus ...
void print_cpp_version() {
    auto const cpp_version = [] () {
        switch (__cplusplus) {
            case 199711L: return "C++98 / C++03";
            case 201103L: return "C++11";
            case 201402L: return "C++14";
            case 201703L: return "C++17";
            case 202002L: return "C++20";
            case 202302L: return "C++23";
            default: return "default case";
        }
    };
    std::cout << "C++ version: " << cpp_version() << std::endl;

    // or
    // std::cout << "C++ version: "; 
    // switch (__cplusplus) {
    //     case 199711L: println("C++98 / C++03"); break;
    //     case 201103L: println("C++11"); break;
    //     case 201402L: println("C++14"); break;
    //     case 201703L: println("C++17"); break;
    //     case 202002L: println("C++20"); break;
    //     case 202302L: println("C++23"); break;
    //     default: println("default case");
    // };
}
