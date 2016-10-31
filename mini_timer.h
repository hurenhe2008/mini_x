/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPRTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  minitimer is based on thread and select model to accomplish *
*           by the way, you can use inherit class thread for taskqueue  *
*           or producter and comsumer queue or other...                 *
*                                                                       *
/***********************************************************************/
#ifndef __MINI_TIMER_H__
#define __MINI_TIMER_H__

#include <windows.h>

class Thread {
public: 
    Thread();
    virtual ~Thread();
    bool start();
    bool stop();
    bool isRunning() const { return (NULL != mh_thread); }

protected:
    virtual void run() = 0;

private:
    static unsigned __stdcall threadproc(void *param);

protected:
    volatile bool mb_torun;

private:
    HANDLE        mh_thread;
    unsigned int  m_threadid;
};


typedef void(*timehander)(void *data);

class MiniTimer : protected Thread {

public:
    MiniTimer();
    virtual ~MiniTimer();

    bool startTimer(timehander handler, void *data, unsigned interval = 1000);
    bool stopTimer();

protected:
    virtual void run();

private:
    MiniTimer(const MiniTimer &);
    MiniTimer & operator= (const MiniTimer&);

    timehander  mp_handler;
    void *      mp_data;
    unsigned    m_interval;   /*milliseconds*/
};




#endif //__MINI_TIMER_H__