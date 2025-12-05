#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string>

using std::string;

// abcab -> abc
// "abcdeaf" -> "bcdeaf" len 6, "abcde" len 5 
// pwwkew -> wke
string foo(const string& str) {
    string longest;
    string temp;
    for (const char ch : str) {
        if (auto pos = temp.find(ch); pos != string::npos) {  // found
            if (temp.size() > longest.size()) longest = temp;
            temp.erase(0, pos+1); // temp is already in longest, clear it
                // e.g. first temp in this scope for "ababc" is : "ab"
        } 
        temp.push_back(ch);
    }

    if (temp.size() > longest.size()) longest = temp;

    return longest;
}


TEST_CASE("temp-1") {
    auto s1 = "ababcdeabcd";
    REQUIRE(foo(s1) == "abcde");

    string s2 = "abcdeaf";
    REQUIRE(foo(s2) == "bcdeaf");

    string s3 = "abba";
    REQUIRE(foo(s3) == "ab");

    string s4 = "aaabcdeaf";
    REQUIRE(foo(s4) == "bcdeaf");

    string s01 = "abcabcbb";
    REQUIRE(foo(s01) == "abc");    // classic repeat after some unique

    string s02 = "bbbbb";
    REQUIRE(foo(s02) == "b");      // all same chars

    string s03 = "pwwkew";
    REQUIRE(foo(s03) == "wke");    // repeat in the middle, longest at the end

    string s04 = "abcdeaf";
    REQUIRE(foo(s04) == "bcdeaf"); 

    string s05 = "abba";
    REQUIRE(foo(s05) == "ab");

    string s06 = "anviaj";
    REQUIRE(foo(s06) == "nviaj");  

    string s07 = "dvdf";
    REQUIRE(foo(s07) == "vdf");    

    string s08 = "tmmzuxt";
    REQUIRE(foo(s08) == "mzuxt");  

    string s09 = "";
    REQUIRE(foo(s09).empty());  

    string s10 = "a";
    REQUIRE(foo(s10) == "a");   
    
    string s11 = "abcd";
    REQUIRE(foo(s11) == "abcd");    
    
    string s12 = "abcdaefghi";
    REQUIRE(foo(s12) == "bcdaefghi");   

    string s13 = "aaaaaaa";
    REQUIRE(foo(s13) == "a");

    string s14 = "abcbacabc";
    REQUIRE(foo(s14) == "abc");
}