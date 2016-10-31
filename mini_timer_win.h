/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPTTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  minitimerwin is based on windows api TimeSetEvent and       *
*           TimeKillEvent to accomplish, provide simple interface call  *
*                                                                       *
/***********************************************************************/
#ifndef __MINI_TIMER_WIN_H__
#define __MINI_TIMER_WIN_H__

#include <Windows.h>
#include <Mmsystem.h>

typedef void(CALLBACK *timehander)(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);

class MiniTimerWin {
public:
    MiniTimerWin();
    ~MiniTimerWin();

    bool startTimer(timehander fun, void *data, unsigned interval = 1000);
    bool stopTimer();
    bool isRunning();

private:
    MiniTimerWin(const MiniTimerWin &);
    MiniTimerWin & operator= (const MiniTimerWin &);

    //unsigned timeinterval;
    MMRESULT  m_timerid;
};


#endif //__MINI_TIMER_WIN_H__