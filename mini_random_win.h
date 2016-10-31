/***********************************************************
*
*   author:  hurh
*   date:    2016/10/17
*
*   desc:    use wincrypt library to generate a real random 
*            number. 
*   note:    thread nosafe;
*
************************************************************/

#ifndef _MINI_RANDOM_WIN_H_
#define _MINI_RANDOM_WIN_H_

#include <windows.h>
#include <wincrypt.h>

#include "mini_def.h"
MINI_NAMESPACE_BEGIN


#if defined(__cplusplus) 
extern "C" {
    bool init_rand_ctx();  /*init context*/
     
    int gen_win_random();  /*gen random number*/
     
    void unit_rand_ctx();  /*unit context*/
}
#endif


class RandomWin{
public:
    RandomWin();
    virtual ~RandomWin();

    int getRandom();

private:
    RandomWin(const RandomWin &);
    RandomWin & operator = (const RandomWin &);

private:
    HCRYPTPROV  m_hCryptCtx;
    int         m_CurRandom;
};



MINI_NAMESPACE_END

#endif /*_MINI_RANDOM_WIN_H_*/