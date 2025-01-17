//
// Created by yujinxiang on 2025/1/17.
//

#ifndef TIMERPROFILE_H
#define TIMERPROFILE_H

#include <iostream>
#include <chrono>
#include <iomanip>

class TimerProfile {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void end() {
        end_time = std::chrono::high_resolution_clock::now();
        printTime();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    void printTime() const {
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Function execution time: " << std::fixed << std::setprecision(4) << duration.count() << " seconds" << std::endl;
    }
};



#endif //TIMERPROFILE_H
