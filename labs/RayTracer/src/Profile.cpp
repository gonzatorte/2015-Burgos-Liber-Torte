#include "Profile.h"

clock_t ini_time(){
    clock_t inited_time = clock();
    return inited_time;
}

float end_time(clock_t inited_time){
    clock_t t = clock() - inited_time;
    return ((float)t)/CLOCKS_PER_SEC;
}
