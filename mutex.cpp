#include "mutex.h"

Mutex::Mutex()
{
	::InitializeCriticalSection(&cs);
}

Mutex::~Mutex()
{
	::DeleteCriticalSection(&cs);
}

void Mutex::lock()
{
	::EnterCriticalSection(&cs);
}

void Mutex::trylock()
{
	::TryEnterCriticalSection(&cs);
}

void Mutex::unlock()
{
	::LeaveCriticalSection(&cs);
}