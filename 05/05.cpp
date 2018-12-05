#include <iostream>
#include <string>
#include <algorithm>
#include <set>

// std::string* was throwing lots of errors, didn't wanted to mess with that
int React(std::string& polymer)
{
    bool hasChanged = false;
    do {
        hasChanged = false;
        for(size_t i = 0; i < polymer.length(); i++) {
            if((polymer[ i ] >= 'a' && polymer[ i ] <= 'z') || (polymer[ i ] >= 'A' && polymer[ i ] <= 'Z')) {
                if((polymer[ i ] - 32 == polymer[ i + 1 ]) || (polymer[ i ] + 32 == polymer[i + 1])) {
                    polymer.erase(i, 2);
                    hasChanged = true;
                }
            }
        }
    } while(hasChanged);
    return polymer.length();
}

int main()
{
    std::string polymer;
    std::cin >> polymer;

    // Part 1
    std::cout << React(polymer) << std::endl;

    // Part 2
    std::set<char> letters;
    for(char c : polymer) {
        char letter = c > 90 ? c - 32 : c;
        letters.insert(letter);
    }
    int mn = polymer.length();
    std::string tmp;
    for(char letter : letters) {
        tmp = polymer;
        tmp.erase(std::remove(tmp.begin(), tmp.end(), letter), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), letter + 32), tmp.end()); 
        int len = React(tmp);
        if(len < mn) {
            mn = len;
        }
    }
    std::cout << mn << std::endl;
    return 0;
}
