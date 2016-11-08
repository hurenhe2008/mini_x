#include "mini_dump.h"
#include <windows.h>
#include <Shlwapi.h>
#include <DbgHelp.h>
#include <time.h>
#include <stdio.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "dbghelp.lib")


#define APP_NAME_MAX_LEN  100
static char s_app_name[APP_NAME_MAX_LEN] = "tmp";

static LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS *exceptinfo);


void catch_unhandle_exception()
{
    ::SetUnhandledExceptionFilter(exception_handler);
}

void catch_unhandle_exception_with(const char *appname)
{
    int len = strlen(appname);
    memcpy_s(s_app_name, APP_NAME_MAX_LEN, appname, len);
    if (len < APP_NAME_MAX_LEN) {
        s_app_name[len] = '\0';
    }
    else {
        s_app_name[APP_NAME_MAX_LEN] = '\0';
    }
    
    ::SetUnhandledExceptionFilter(exception_handler);
}

static HANDLE create_dump_file()
{
    char file_path[MAX_PATH] = { 0 };

    if (0 == ::GetModuleFileNameA(NULL, file_path, MAX_PATH)) {
        return INVALID_HANDLE_VALUE;
    }

    char time_now[100] = { 0 };
    SYSTEMTIME systime;
    //::GetSystemTime(&systime);   /*GMT*/
    ::GetLocalTime(&systime);      /*Localtime*/
    sprintf_s(time_now, sizeof time_now, "_%04d-%02d-%02d_%02d-%02d-%02d",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute, systime.wSecond);

    ::PathRemoveFileSpecA(file_path);
    strcat_s(file_path, sizeof file_path, "\\");
    strcat_s(file_path, sizeof file_path, s_app_name);   /*app name*/
    strcat_s(file_path, sizeof file_path, time_now);     /*time*/
    strcat_s(file_path, sizeof file_path, ".dmp");

    ::OutputDebugStringA("dump file path:");
    ::OutputDebugStringA(file_path);

    return ::CreateFileA(file_path, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS *exceptinfo)
{
    ::OutputDebugStringA("catch new exception!!!");

    HANDLE hfile = create_dump_file();
    if (INVALID_HANDLE_VALUE == hfile) {
        ::OutputDebugStringA("create dump file failed!!!");
        return EXCEPTION_CONTINUE_SEARCH;
    }

    MINIDUMP_EXCEPTION_INFORMATION dumpinfo;
    dumpinfo.ThreadId = ::GetCurrentThreadId();
    dumpinfo.ExceptionPointers = exceptinfo;
    dumpinfo.ClientPointers = true;  
    MINIDUMP_TYPE type = MiniDumpNormal;  
    BOOL bret = ::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(),
        hfile, type, &dumpinfo, NULL, NULL);

    ::CloseHandle(hfile);
    return bret ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}