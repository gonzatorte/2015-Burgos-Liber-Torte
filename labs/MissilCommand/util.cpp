#include "util.h"

#ifdef __unix__
#include <unistd.h>
#else
#include <windows.h>
#endif // __unix__


void sleep(long millis){
#ifdef __unix__
    return usleep(millis*1000);
#else
    return Sleep(millis);
#endif // __unix__
}
