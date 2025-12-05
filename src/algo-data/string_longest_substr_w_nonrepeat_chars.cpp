#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string>

using std::string;

// abcab -> abc
// "abcdeaf" -> "bcdeaf" len 6, "abcde" len 5 
// pwwkew -> wke
string longest_substr_w_nonrepeat_chars(const string& str) {
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
    REQUIRE(longest_substr_w_nonrepeat_chars(s1) == "abcde");

    string s2 = "abcdeaf";
    REQUIRE(longest_substr_w_nonrepeat_chars(s2) == "bcdeaf");

    string s3 = "abba";
    REQUIRE(longest_substr_w_nonrepeat_chars(s3) == "ab");

    string s4 = "aaabcdeaf";
    REQUIRE(longest_substr_w_nonrepeat_chars(s4) == "bcdeaf");

    string s01 = "abcabcbb";
    REQUIRE(longest_substr_w_nonrepeat_chars(s01) == "abc");    // classic repeat after some unique

    string s02 = "bbbbb";
    REQUIRE(longest_substr_w_nonrepeat_chars(s02) == "b");      // all same chars

    string s03 = "pwwkew";
    REQUIRE(longest_substr_w_nonrepeat_chars(s03) == "wke");    // repeat in the middle, longest at the end

    string s04 = "abcdeaf";
    REQUIRE(longest_substr_w_nonrepeat_chars(s04) == "bcdeaf"); 

    string s05 = "abba";
    REQUIRE(longest_substr_w_nonrepeat_chars(s05) == "ab");

    string s06 = "anviaj";
    REQUIRE(longest_substr_w_nonrepeat_chars(s06) == "nviaj");  

    string s07 = "dvdf";
    REQUIRE(longest_substr_w_nonrepeat_chars(s07) == "vdf");    

    string s08 = "tmmzuxt";
    REQUIRE(longest_substr_w_nonrepeat_chars(s08) == "mzuxt");  

    string s09 = "";
    REQUIRE(longest_substr_w_nonrepeat_chars(s09).empty());  

    string s10 = "a";
    REQUIRE(longest_substr_w_nonrepeat_chars(s10) == "a");   
    
    string s11 = "abcd";
    REQUIRE(longest_substr_w_nonrepeat_chars(s11) == "abcd");    
    
    string s12 = "abcdaefghi";
    REQUIRE(longest_substr_w_nonrepeat_chars(s12) == "bcdaefghi");   

    string s13 = "aaaaaaa";
    REQUIRE(longest_substr_w_nonrepeat_chars(s13) == "a");

    string s14 = "abcbacabc";
    REQUIRE(longest_substr_w_nonrepeat_chars(s14) == "abc");
}