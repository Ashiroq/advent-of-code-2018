#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <unordered_map>

enum EventType {
    Wakes, FallsAsleep, BeginsShift
};

struct Data {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    EventType eType;
    std::string message;
    int guardId = -1;
};

bool cmp(Data a, Data b) {
    if(a.month < b.month)
        return true;
    else if(a.month == b.month) {
        if(a.day < b.day)
            return true;
        else if(a.day == b.day) {
            if(a.hour < b.hour)
                return true;
            else if(a.hour == b.hour) {
                if(a.minute < b.minute) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int n = 1159;
    std::vector<Data> data(n);
    for(int i = 0; i < n; i++) {
        std::string line;
        std::getline(std::cin, line, '\n');
        std::istringstream iss(line);
        iss.ignore(1); // '['
        iss >> data[ i ].year; 
        iss.ignore(1); // '-'
        iss >> data[ i ].month; 
        iss.ignore(1); // '-'
        iss >> data[ i ].day; 
        iss.ignore(1); // ' '
        iss >> data[ i ].hour; 
        iss.ignore(1); // ':'
        iss >> data[ i ].minute; 
        iss.ignore(2); // '] '
        getline(iss, data[ i ].message, '\n');

        if(data[ i ].message.find("asleep") != std::string::npos)
            data[ i ].eType = FallsAsleep;
        else if(data[ i ].message.find("wakes") != std::string::npos)
            data[ i ].eType = Wakes;
        else {
            data[ i ].eType = BeginsShift;
            std::istringstream iss2(data[ i ].message);
            iss2.ignore(data[ i ].message.find("#") + 1);
            iss2 >> data[ i ].guardId;
        }
    }
    sort(data.begin(), data.end(), cmp);
//    for(Data d : data) {
//        printf("[%i-%02i-%02i %02i:%02i] %s\n", d.year, d.month, d.day, d.hour, d.minute, d.message.c_str());
//    }

    std::unordered_map<int, int*> guards;
    // For Part 2
    std::unordered_map<int, int> totalMinutes;

    int currentGuard;
    int sleepStartHour;
    int sleepStartMinute;
    for(int i = 0; i < n; i++) {
        Data d = data[ i ];
        if(d.eType == BeginsShift) {
            currentGuard = d.guardId;
            if(guards.count(d.guardId) == 0) { 
                    guards[ d.guardId ] = new int[ 60 ];
                    for(int i = 0; i < 60; i++)
                        guards[ d.guardId ][ i ] = 0;
            }
        }
        else if(d.eType == FallsAsleep) {
            sleepStartHour = d.hour;
            sleepStartMinute = d.minute;
        }
        else if(d.eType == Wakes) {
            int h = sleepStartHour;
            int m = sleepStartMinute;
            if(totalMinutes.count(currentGuard) == 0)
                totalMinutes[ currentGuard ] = 0;
            while(h != d.hour || m != d.minute) {
                if(m >= 60) {
                    m %= 60;
                    h = (h + 1) % 24;
                }
                if(h == 0) {
                    ++guards[ currentGuard ][ m ];
                    ++totalMinutes[ currentGuard ];
                }
                ++m;
            }
        }
    }
    for(auto p : guards) {
        printf("Guard #%i: \n", p.first);
        // For Part 1
        std::pair<int, int> mx = std::make_pair(0, p.second[ 0 ]);

        for(int i = 0; i < 60; i++) {
            if(p.second[ i ] > mx.second) {
                mx.second = p.second[ i ];
                mx.first = i;
            }
            if(p.second[ i ] != 0)
                printf("%02i: %i\n", i, p.second[ i ]);
        }
        printf("Max: \n\t%02i: %i\n", mx.first, mx.second);
        printf("Total minutes: %i\n", totalMinutes[ p.first ]);
    }

    for(auto p : guards)
        delete p.second;
    return 0;
}
