/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPRTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  mini_dump is based on windows dbghelp with minidump to      *
*           trace unhandled exception, the best way is calling the      *
*           interface at the begin of main.                             *
*                                                                       *
/***********************************************************************/
#ifndef __MINI_DUMP_H__
#define __MINI_DUMP_H__


/**
* fuction:   catch_unhandle_exception
* param:     no
* purpose:   aim to catch uncatched exception and write to dump file.   
*            note that catch_unhandle_exception must call when main start.
**/
void catch_unhandle_exception();


#endif //__MINI_DUMP_H__