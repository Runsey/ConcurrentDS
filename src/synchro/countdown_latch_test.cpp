#include "countdown_latch.hpp"
#include <future>
#include <iostream>
#include <cassert>
#include <deque>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include<algorithm>

using namespace std;
using namespace synchro;

int main(int argc, char** argv){
    unsigned seed;
    if(argc==2) seed= atoi(argv[1]);
    else seed= time(nullptr); //allows us to start aranodm seed

    cout<<"Starting test"<<endl;
    const int test_size= 100;
    countdown_latch starting_latch{test_size};
    vector<future<void>> threads;
    deque<countdown_latch> test;
    for(int i=0;i<test_size;++i){
        test.emplace_back(i+1);
    }

    bool start[test_size]={false};
    for(int i=0;i<test_size;++i){
        threads.push_back(async(launch::async, [&](int idx){
            vector<int> wait_order(test_size);
            iota(wait_order.begin(),wait_order.end(),0);
            default_random_engine gen;
            gen.seed(idx+seed);
            random_shuffle(wait_order.begin(), wait_order.end(), [&gen](int max){ return gen() % max;} );
            for(bool b: start){
                assert(!b);
            }
            starting_latch.count_down();
            starting_latch.wait();
            start[idx]=true;
            for(int j=idx;j<test_size;++j){
                test[j].count_down();
            }
            
            for(int j=idx;j<test_size;++j){
                test[j].wait();
                assert(start[j]);
            }
        },i));
    }

    for(auto& fut: threads){
        fut.get();
    }

    cout<<"Sucess"<<endl;        
    }
