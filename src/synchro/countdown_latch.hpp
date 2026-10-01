#include<iostream>
#include<atomic>
#include<mutex>
#include<condition_variable>

using namespace std;
#pragma once
namespace synchro{
class countdown_latch{
    private: 
    atomic<int> down;
    mutex m;
    condition_variable cv;

    public:
        countdown_latch() =delete;
        countdown_latch(int wait);
        void count_down();
        void wait();
        void reset(int wai);
        int get();
        ~countdown_latch();
};

}

