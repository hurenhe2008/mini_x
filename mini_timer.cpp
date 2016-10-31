#include "mini_timer.h"
#include <process.h>
#include <WinSock2.h>
#include "log.h"

#pragma comment(lib, "ws2_32.lib")

Thread::Thread()
: mb_torun(false)
, mh_thread(NULL)
, m_threadid(0)
{

}

Thread::~Thread()
{
    stop();
}

bool Thread::start()
{
    if (NULL != mh_thread) {
        return true;
    }

    mb_torun = true;   /*set flag*/

    mh_thread = (HANDLE)_beginthreadex(NULL, 0, threadproc, this, 0, &m_threadid);

    return (NULL != mh_thread) ? true : false;
}

bool Thread::stop()
{
    if (NULL == mh_thread) {
        return true;
    }

    mb_torun = false;  /*exit loop*/
    
    if (WAIT_OBJECT_0 != WaitForSingleObject((HANDLE)mh_thread, INFINITE)) {
        log_main_error("Wait timer thread handle return not WAIT_OBJECT_0!");
        abort();   /*exit direct!!!*/
    }

    DWORD exitcode = 0;
    if (!GetExitCodeThread(mh_thread, &exitcode)) {
        log_main_error("GetExitCodeThread of timer thread failed!!!");
    }

    if (0 != exitcode) {
        log_main_error("run timer thread error with threadproc param convert wrong!");
    }

    CloseHandle(mh_thread);
    mh_thread = NULL;

    return true;
}

unsigned __stdcall Thread::threadproc(void *param)
{
    Thread *self = reinterpret_cast<Thread *>(param);
    if (!self) {
        return -1;   /*error*/
        /*abort();*/
    }

    self->run();

    return 0;
}


////////////////////////////////////////////////////////////////////////
MiniTimer::MiniTimer()
: mp_handler(NULL)
, mp_data(NULL)
, m_interval(0)
{
    /*fuck windows, must call WSAStartup to init winsock*/
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}

MiniTimer::~MiniTimer()
{
    stopTimer();

    /*fuck windows, must call WSACleanup to release winsock*/
    WSACleanup();
}

bool MiniTimer::startTimer(timehander handler, void *data, unsigned interval)
{
    stopTimer();

    if (!handler || !data) {
        log_main_error("timehander or data is null when startTimer!!!");
        return false;
    }

    m_interval = ((interval > 0) ? interval : 1000);
    mp_handler = handler;
    mp_data = data;

    return Thread::start();
}

bool MiniTimer::stopTimer()
{
    Thread::stop();

    m_interval = 0;
    mp_handler = NULL;
    mp_data = NULL;

    return true;
}

void MiniTimer::run()
{
    timeval interval;
    interval.tv_sec = (m_interval < 1000) ? 0 : (m_interval / 1000);  
    interval.tv_usec = (m_interval < 1000) ? (m_interval * 1000) : ((m_interval % 1000) * 1000); 

    /*fuck windows, directly use select without socket and fd_set in linux*/
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    fd_set set;

    int ret = 0;
    while (mb_torun) {

        FD_ZERO(&set);
        FD_SET(sock, &set);

        ret = select(sock + 1, &set, NULL, NULL, &interval);

        if (ret < 0) {
            break;
        }
       
        mp_handler(mp_data);   /*callback*/
    }   
}