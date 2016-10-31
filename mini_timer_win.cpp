#include "mini_timer_win.h"
#include "log.h"
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")

MiniTimerWin::MiniTimerWin():
m_timerid(0)
{

}

MiniTimerWin::~MiniTimerWin()
{

}

bool MiniTimerWin::startTimer(timehander fun, void *data, unsigned interval)
{
    if (0 != m_timerid) {
        stopTimer();
    }

    m_timerid = ::timeSetEvent(interval, 0, fun, (DWORD_PTR)data, TIME_PERIODIC);

    if (0 == m_timerid) {
        return false;
    }
    return true;
}

bool MiniTimerWin::stopTimer()
{
    if (0 == m_timerid) {
        return true;
    }

    if (TIMERR_NOERROR != ::timeKillEvent(m_timerid)) {
        log_main_error("timeKillEvent call error (timeid: %d)!!!", m_timerid);
        abort();  /*exit dirrect!!!*/
    }

    m_timerid = 0;
    return true;
}

bool MiniTimerWin::isRunning()
{
    return (0 != m_timerid) ? true : false;
}