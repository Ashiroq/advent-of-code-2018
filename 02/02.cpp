#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <string>

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> data(n);

    for(int i = 0; i < n; i++)
        std::cin >> data[ i ];

    // Part 1
    int doubledLetters = 0;
    int tripledLetters = 0;
    for(std::string s : data) {
        std::unordered_map<char, int> chars;
        for(char c : s) {
            if(chars.count(c) == 0)
                chars[c] = 1;
            else
                chars[c]++;
        }
        bool hasPair = false;
        bool hasTriplet = false;
        for(auto p : chars)  {
            if(!hasPair && p.second == 2) {
                ++doubledLetters;
                hasPair = true;
            }
            if(!hasTriplet && p.second == 3) {
                ++tripledLetters;
                hasTriplet = true;
            }
        }
    }
    std::cout << doubledLetters * tripledLetters << std::endl;
    
    // Part 2
    for(std::string s1 : data) {
        for(std::string s2 : data) {
            if(s1 == s2)
                continue;
            std::string core = "";
            int diff = 0;
            for(int i = 0; diff < 2 && i < s1.size(); i++) {
                if(s1[ i ] == s2[ i ])
                    core += s1[ i ];
                else
                    diff++;
            }
            if(diff < 2)
                std::cout << core << std::endl;
        }
    }
    return 0;
}
