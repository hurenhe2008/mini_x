#include "mini_dump.h"
#include <windows.h>
#include <Shlwapi.h>
#include <DbgHelp.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "dbghelp.lib")

static LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS *exceptinfo);


void catch_unhandle_exception()
{
    ::SetUnhandledExceptionFilter(exception_handler);
}

static HANDLE create_dump_file()
{
    char file_path[MAX_PATH] = { 0 };

    if (0 == ::GetModuleFileNameA(NULL, file_path, MAX_PATH)) {
        return INVALID_HANDLE_VALUE;
    }

    ::PathRemoveFileSpecA(file_path);
    ::PathAppendA(file_path, "\\");
    ::PathAppendA(file_path, "DeviceMgr.dmp");   /*app name*/

    return ::CreateFileA(file_path, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS *exceptinfo)
{
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