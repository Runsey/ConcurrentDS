#include "countdown_latch.hpp"

namespace synchro{

countdown_latch::countdown_latch(int wait) : down(wait) {}

void countdown_latch::count_down(){
    down--;
}

void countdown_latch::wait(){
    down.wait(0);
}

void countdown_latch::reset(int wait){
    down.store(wait);
}

countdown_latch::~countdown_latch(){
    
}

}