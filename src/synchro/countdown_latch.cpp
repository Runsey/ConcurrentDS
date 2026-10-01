#include "countdown_latch.hpp"

namespace synchro{

countdown_latch::countdown_latch(int wait) : down(wait) {}

void countdown_latch::count_down(){
    if(down.fetch_sub(1)==1){
        down.notify_all();
    }

}

void countdown_latch::wait(){
    int current=down.load();
    while(current!=0){
        down.wait(current);
        current=down.load();
    }
}

void countdown_latch::reset(int wait){
    down.store(wait);
}

int countdown_latch::get(){
    return down.load();
}

countdown_latch::~countdown_latch(){
    
}

}