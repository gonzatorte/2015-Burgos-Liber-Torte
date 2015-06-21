#include "Profile.h"

clock_t inited_time;

void ini_time(){
    inited_time = clock();
}

float end_time(){
    clock_t t = clock() - inited_time;
    return ((float)t)/CLOCKS_PER_SEC;
}
