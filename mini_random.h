/***************************************************************
*
*   author:  hurh
*   date:    2016/10/17
*
*   desc:    use srand and random to generate pseudo-random 
*            number.
*
*   note:    use gen_random or Random class in single thread.
*            because srand/rand depends on thread block struct
*            info.
*
****************************************************************/

#ifndef _MINI_RANDOM_H_
#define _MINI_RANDOM_H_


#include "mini_def.h"
MINI_NAMESPACE_BEGIN

#ifdef __cplusplus
extern "C" {
    int gen_random();
}
#endif 


class Random {
public:
    Random();
    virtual ~Random();

    int getRandom();

private:
    Random(const Random &);
    Random & operator = (const Random &);
};


MINI_NAMESPACE_END

#endif /*_MINI_RANDOM_H_*/