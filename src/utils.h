#include <iostream>

//// Notes:
// - `inline` fns are used to allow multiple definitions when `ct *` used

/// Returns last `n` hex digit of `ptr`
inline std::string last_n_digit(void* ptr, size_t n) {
    std::stringstream ss;
    ss << std::hex << std::setw(n) << std::setfill('0')
       << (reinterpret_cast<uintptr_t>(ptr) & 0xFFFF);
    return ss.str();
}

///
template<typename T>
T&& println(T&& value) {
    std::cout << value << std::endl;
    return std::forward<T>(value);
}


///
template<typename T>
T&& print(T&& value) {
    std::cout << value;
    return std::forward<T>(value);
}


///
template<typename T>
T&& debug_print(const char* expr, T&& value, const char* file = __FILE__, int line = __LINE__) {
    std::cerr << "[" << file << ":" << line << "] " << expr << " = " << value << std::endl;
    return std::forward<T>(value);
}

#define dbg(x) debug_print(#x, x)


///
#define print_vec(vec) print_vec_(vec, #vec)

inline void print_vec_(const std::vector<int>& vec, const std::string& name) {
    std::cout << name << ": ";
    for (int e : vec) std::cout << e << " ";
    std::cout << std::endl;
}


/// cpp version
/// Note: works with this usage: cl /Zc:__cplusplus ...
inline void print_cpp_version() {
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
    std::cout << "=== C++ version: " << cpp_version() << std::endl << std::endl;

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
