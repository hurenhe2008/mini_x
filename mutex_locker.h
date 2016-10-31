/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPRTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  MutexLocker class provide the constructor and distructor to *
*           accomplish Mutex's lock and unlock.                         *
*                                                                       *
* note:     forbid to recursive or reenter call MutexLocker with the    *  
*           same Mutex in case deadlock.                                *
*                                                                       *
*                                                                       *
/***********************************************************************/
#ifndef _MUTEX_LOCKER_H_
#define _MUTEX_LOCKER_H_

class Mutex;

class MutexLocker{
public:
    MutexLocker(Mutex &mutex);
    ~MutexLocker();

private:
    MutexLocker(const MutexLocker &);   //forbidden copy and assign
    MutexLocker & operator =(const MutexLocker &);

private:
    Mutex &m_InnerMutex;

};

#endif //_MUTEX_LOCKER_H_