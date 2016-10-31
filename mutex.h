/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPRTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  mutex is based on windows critical section to accomplish    *
*           CRITICAL_SECTION is recursived to call with counter, but    *
*           advise not to recursive or reenter to call for deadlock.    *
*           choice CRITICAL_SECTION with lightweight mechanism.         *
*                                                                       *
* note:     try avoid use Mutex or CRITICAL_SECTION directly in code.   *
*           the best way to call them in constructor and distructor in  *
*           scoped code, so we provide a MutexLocker class.             *
*                                                                       *
/***********************************************************************/
#pragma once
#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <Windows.h>

class Mutex {
public:
	Mutex();
	~Mutex();

	void lock();
	void trylock();
	void unlock();
	
private:
	Mutex(const Mutex &);     //forbidden copy and assign
	Mutex & operator =(const Mutex &);

private:
	CRITICAL_SECTION cs;
};

#endif
