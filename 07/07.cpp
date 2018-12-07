#include <vector>
#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

int main()
{
    int V = 26;
    int E = 101;
    std::vector<int> neighb[ V ];
    std::vector<int> predecessors[ V ];
    std::vector<int> indegs(V); // degree incoming
    
    for(int i = 0; i < V; i++)
        indegs[ i ] = 0;

    for(int i = 0; i < E; i++) {
        char pred, succ;
        scanf("Step %c must be finished before step %c can begin.\n", &pred, &succ);
        neighb[ pred - 'A' ].push_back(succ - 'A');
        predecessors[ succ - 'A' ].push_back(pred - 'A');   // For Part 2
        ++indegs[ succ - 'A' ];
    }

    auto cmp = [](int a, int b){ return a > b; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> list(cmp);
    std::priority_queue<int, std::vector<int>, decltype(cmp)> available(cmp);   // For Part 2
    for(int i = 0; i < V; i++) {
        if(indegs[ i ] == 0) {
            list.push(i);
            available.push(i);
        }
    }

    // Part 1
    std::string order = "";
    while(!list.empty()) {
        int p = list.top();
        order += p + 'A';
        list.pop();
        for(int el : neighb[ p ]) {
            --indegs[ el ];
            if(indegs[ el ] == 0) {
                list.push(el);
            }
        }
    }
    std::cout << order << std::endl;

    // Part2
    int n = 26;
    int w = 5;
    int base = 60;
    int remaining[ n + 1 ];  // remaining[ n ] is infinite idle state
    int workers[ w ];
    std::set<int> completed;
    int totalTime = 0;
    
    for(int i = 0; i < n; i++)
        remaining[ i ] = base + i + 1;  // A increases by 1 not 0
    remaining[ n ] = 1;
    for(int i = 0; i < w; i++)
        workers[ i ] = n;

    while(completed.size() != n) {
        for(int i = 0; i < w; i++) {
            if(remaining[ workers[ i ] ] == 0) {
                int el = workers[ i ];
                std::cerr << "[LOG] Worker " << i << " completed a job: " << char(el + 'A') << std::endl;

                completed.insert(el);
                for(int i = 0; i < neighb[ el ].size(); i++) {
                    int currentNeighb = neighb[ el ][ i ];
                    
                    // If all predecessors are completed, add it as available
                    bool isAvailable = true;
                    for(int pred : predecessors[ currentNeighb ]) {
                      if(completed.count(pred) == 0) {
                          isAvailable = false;
                          break;
                      }
                    }
                    if(isAvailable) {
                        std::cerr << "[LOG] Added " << char(currentNeighb + 'A') << " as available job." << std::endl;
                        available.push(currentNeighb);
                    } 
                }
                // Marking as idle
                workers[ i ] = n;
                std::cerr << "[LOG] Worker " << i << " is idle." << std::endl;
            }
            
            // Finding a job
            if(workers[ i ] == n) {
                if(!available.empty()) {
                    workers[ i ] = available.top();
                    available.pop();
                    std::cerr << "[LOG] Worker " << i << " found a job: " << char(workers[ i ] + 'A') << std::endl;
                }
            } 

            // Progress time
            if(workers[ i ] != n) {
                --remaining[ workers[ i ] ];
                std::cerr << "[LOG] Worker " << i << " working on: " << char(workers[ i ] + 'A');
                std::cerr << " (" <<  remaining[ workers[ i ] ] << " / " << base + workers[i] + 1 << ")" << std::endl;
            }
        }
        ++totalTime;
    }
    --totalTime;
    std::cerr << "Total time: " << totalTime << std::endl;
    std::cout << totalTime << std::endl;
    return 0;
}
