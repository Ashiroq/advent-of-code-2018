#include <iostream>
#include <vector>
#include <cstdio>
#include <set>

struct Claim {
    int id;
    int offsetLeft;
    int offsetTop;
    int width;
    int height;
};

int main()
{
    int n = 1397;
    int m = 1100;
    std::vector<Claim> claims(n);

    for(int i = 0; i < n; i++) {
        scanf("#%i @ %i, %i: %ix%i\n", &(claims[ i ].id), &(claims[ i ].offsetLeft), &(claims[ i ].offsetTop), 
                                         &(claims[ i ].width), &(claims[ i ].height));
    }

    // Part 1
    int** grid = new int*[ m ];
    
    for(int j = 0; j < m; j++) {
        grid[ j ] = new int[ m ];
        for(int i = 0; i < m; i++)
            grid[ j ][ i ] = 0;
    }

    for(int i = 0; i < n; i++) {
        for(int x = claims[ i ].offsetLeft; x < claims[ i ].offsetLeft + claims[ i ].width; x++) {
            for(int y = claims[ i ].offsetTop; y < claims[ i ].offsetTop + claims[ i ].height; y++)
                ++grid[ x ][ y ];
        }
    }

    int counter = 0;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[ i ][ j ] >= 2)
                ++counter;
        }
    }
    std::cout << counter << std::endl;

    // Part 2
    std::set<int> overlapping;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j)
                continue;
            Claim c1 = claims[ i ];
            Claim c2 = claims[ j ];
            if((c1.offsetLeft < c2.offsetLeft + c2.width) && (c1.offsetTop < c2.offsetTop + c2.height) && 
               (c2.offsetLeft < c1.offsetLeft + c1.width) && (c2.offsetTop < c1.offsetTop + c1.height)) {
                overlapping.insert(c1.id);
            }
        }
    }
    for(int i = 0; i < n; i++)
        if(overlapping.count(claims[ i ].id) == 0)
            std::cout << claims[ i ].id << std::endl;
    for(int i = 0; i < m; i++)
        delete grid[ i ];
    delete grid;
    return 0;
}
