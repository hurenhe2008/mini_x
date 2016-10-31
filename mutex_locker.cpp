#include "mutex_locker.h"
#include "mutex.h"

MutexLocker::MutexLocker(Mutex &mutex)
: m_InnerMutex(mutex)
{
    m_InnerMutex.lock();
}

MutexLocker::~MutexLocker()
{
    m_InnerMutex.unlock();
}