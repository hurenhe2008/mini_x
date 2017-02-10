/*******************************************************************
*
*   author:  hurenhe
*
*   date:    2017/2/10
*
*   declare: accomplish memory series operation function.
*
********************************************************************/

#ifndef _XSTRING_H_
#define _XSTRING_H_

#ifdef __cplusplus
    #define CAPI extern "C"
#else
    #define CAPI
#endif 

/***
* @function  
*          xmemset()
* @param
*          dst - the destination buffer 
*          ch -  replaced value
*          n -   replaced count
* @return
*          if success, return the dst address 
*          otherwise return nullptr
*/
CAPI void* xmemset(void *dst, int ch, unsigned n);


/***
* @function
*          xmemcpy()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   copy count
* @return
*          if success, return the dst address
*          otherwise return nullptr
*/
CAPI void* xmemcpy(void *dst, const void *src, unsigned n);


/***
* @function
*          xmemmove()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   move count
* @return
*          if success, return the dst address 
*          otherwise return nullptr
*/
CAPI void* xmemmove(void *dst, const void *src, unsigned n);


/***
* @function
*          xmemcmp()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   move count
* @return
*          if equal front n byte, return 0
*          otherwise return -1
*/
CAPI int xmemcmp(const void *dst, const void *src, unsigned n);


/***
* @function
*          xmemcpy_s()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   move count
* @return
*          if success, return 0
*          otherwise return -1
*/
CAPI int xmemcpy_s(void *dst, unsigned size, const void *src, unsigned n);


/***
* @function
*          xmemmove_s()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   move count
* @return
*          if success, return 0
*          otherwise return -1
*/
CAPI int xmemmove_s(void *dst, unsigned size, const void *src, unsigned n);


#endif //_XSTRING_H_