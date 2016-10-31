#include "mini_singleton.h"
#include <windows.h>

//#define _USE_DATA_SEG_
//#define _USE_MUTEX_

#ifdef _USE_DATA_SEG_       
#pragma data_seg("Shared")
volatile int g_AppIns = 0;
#pragma data_seg()
#pragma comment(linker, "/section:Shared,RWS")
#endif


bool is_app_exist()
{
#ifdef _USE_DATA_SEG_
    if(++g_AppIns > 1) {
        return true;
    }
#else 
    #ifdef _USE_MUTEX_
        CreateMutexA(NULL, FALSE, "DeviceMgr.Mutex");
    #else
        CreateEventA(NULL, TRUE, FALSE, "DeviceMgr.Event");
    #endif
        if (ERROR_ALREADY_EXISTS == GetLastError()) {
            return true;
        }
#endif

    return false;
}

