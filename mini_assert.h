/***********************************************************
*
*   author:  hurh
*   date:    2016/10/17
*
*   desc:    assert unexpected condition happen. 
*            
*   note:    if under visual studio, use crtdbg.h, 
*            or use C/C++ runtime assert.h for assert
*
************************************************************/

#ifndef _MINI_ASSERT_H_
#define _MINI_ASSERT_H_

#include "mini_def.h"
MINI_NAMESPACE_BEGIN


#ifndef _DEBUG
#define Assert(x)       (void)0;
#define Assert_Str(x)   (void)0;
#else 
#ifdef _MSC_VER
#include <crtdbg.h>
#define Assert(x)       _ASSERT(x)
#define Assert_Str(x)   _ASSERTE(x)
#else
#include <assert.h>
#define Assert(x)       assert(x)
#define Assert_Str(x)   assert(x)
#endif
#endif


MINI_NAMESPACE_END

#endif /*_MINI_ASSERT_H_*/