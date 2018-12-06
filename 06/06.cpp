#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>

#define DISTANCE_THRESHOLD 10000

int main()
{
    int n = 50;
    std::vector<std::pair<int, int>> coords(n);
    for(int i = 0; i < n; i++)
        scanf("%i, %i\n", &coords[ i ].first, &coords[ i ].second);

    int minX = coords[ 0 ].second;
    int maxX = coords[ 0 ].second;
    int minY = coords[ 0 ].first;
    int maxY = coords[ 0 ].first;
    for(auto p : coords) {
        if(p.second < minX)
            minX = p.second;
        if(p.second > maxX)
            maxX = p.second;
        if(p.first < minY)
            minY = p.first;
        if(p.first > maxY)
            maxY = p.first;
    }
    
    int rowsCount = maxX - minX + 1;
    int colsCount = maxY - minY + 1;
    int** points = new int*[ rowsCount ];
    for(int i = 0; i < rowsCount; i++) {
        points[ i ] = new int[ colsCount ];
    }

    // Part 1
    // Every point on the grid is marked by the index of the closest point in coords.
    // If there is no the closest, then the value is 66.
    int firstMin = 1e5;
    int secondMin = 1e5;
    int pointIndex;
    for(int i = 0; i < rowsCount; i++) {
        for(int j = 0; j < colsCount; j++) {
            firstMin = 1e5; 
            secondMin = 1e5;
            int x = minX + i;
            int y = minY + j;
            for(int k = 0; k < coords.size(); k++) {
                auto p = coords[ k ];
                int dist = std::abs(p.second - x) + std::abs(p.first - y); 
                if(dist <= firstMin) {
                    secondMin = firstMin;
                    pointIndex = k;
                    firstMin = dist;
                }
            }
            if(firstMin == secondMin)
                points[ i ][ j ] = 66;
            else
                points[ i ][ j ] = pointIndex;
        }
    }

    std::set<int> infinite;
    std::ofstream out("part1.txt");
    for(int i = 0; i < rowsCount; i++) {
        for(int j = 0; j < colsCount; j++) {
            // Every point on the edge is from infinite group, so mark group as one.
            if(i == 0 || j == 0 || i == rowsCount - 1 || j == colsCount - 1)
                infinite.insert(points[ i ][ j ]);
            out << (points[ i ][ j ] < 10 ? "0" : "") << points[ i ][ j ] << " ";
        }
        out << std::endl;
    }
    out.close();

    std::ifstream read("part1.txt");
    std::string line;
    int index;
    std::unordered_map<int, int> counts;
    while(std::getline(read, line, '\n')) {
        std::istringstream iss(line);
        while(iss >> index) {
            if(infinite.count(index) == 0)
                ++counts[ index ];
        }
    }
    int maxValue = -1;
    for(auto p : counts) {
        if(p.second > maxValue)
            maxValue = p.second;
    }
    printf("%i\n", maxValue);
    read.close();

    // Part 2
    // Writing to file isn't actually necessary, but hey I want to look at that pattern ;)
    int distSum = 0;
    int sizeCounter = 0;
    out.open("part2.txt");
    for(int i = 0; i < rowsCount; i++) {
        for(int j = 0; j < colsCount; j++) {
            int x = minX + i;
            int y = minY + j;
            distSum = 0;
            for(int k = 0; k < coords.size(); k++)
                distSum += std::abs(coords[ k ].second - x) + std::abs(coords[ k ].first - y); 
            if(distSum <= DISTANCE_THRESHOLD) {
                points[ i ][ j ] = 1;
                ++sizeCounter;
            }
            else
                points[ i ][ j ] = 0;
            out << points[ i ][ j ] << " ";
        }
        out << std::endl;
    }
    out.close();
    printf("%i\n", sizeCounter);

    for(int i = 0; i < rowsCount; i++)
        delete[] points[ i ];
    delete[] points;
    return 0;
}
