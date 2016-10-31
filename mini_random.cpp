#include "mini_random.h"

#include <time.h>
#include <stdlib.h>
#include <process.h>

static bool binit = false;


MINI_NAMESPACE_BEGIN

int gen_random()
{
    if (!binit) {
        int seek = (int)time(NULL) + _getpid();     /*time and process id*/
        srand(seek);
        binit = true;
    }

    return rand();
}


Random::Random()
{
    srand((int)time(NULL) + _getpid());
}

Random::~Random()
{

}

int Random::getRandom()
{
    return rand();
}


MINI_NAMESPACE_END