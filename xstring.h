/*******************************************************************
*
*   author:  hurenhe
*
*   date:    2017/2/10
*
*   declare: accomplish memory series operation function and
*            string series operation function.
*
********************************************************************/

#ifndef _XSTRING_H_
#define _XSTRING_H_

#ifdef __cplusplus
    #define CAPI extern "C"
#else
    #define CAPI
#endif 

//================================ memory.h ===================================

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



//================================ string.h ===================================


/***
* @function
*          xstrlen()
* @param
*          src - the source buffer
* @return
*          return src buffer length       
*/
CAPI unsigned xstrlen(const char *src);


/***
* @function
*          xstrcmp()
* @param
*          dst - the destination buffer
*          src - the source buffer
*          n -   move count
* @return
*          src1 < src2, return -1
*          src1 = src2, return 0
*          src1 > src2, return 1        
*/
CAPI int xstrcmp(const char *src1, const char *src2);


/***
* @function
*          xstrcpy()
* @param
*          dst - the destination buffer
*          src - the source buffer
* @return
*          if success, return dst addr
*          if fail, return nullptr
*/
CAPI char* xstrcpy(char *dst, const char *src);


/***
* @function
*          xstrcat()
* @param
*          dst - the destination buffer
*          src - the source buffer
* @return
*          if success, return dst addr
*          if fail, return nullptr
*/
CAPI char* xstrcat(char *dst, const char *src);


/***
* @function
*          xstrstr()
* @param
*          dst - the destination buffer
*          src - the source buffer
* @return
*          if success, return the address with src first found in dst
*          if fail, return nullptr
*/
CAPI char* xstrstr(const char *dst, const char *src);


/***
* @function
*          xstrrstr()
* @param
*          dst - the destination buffer
*          src - the source buffer
* @return
*          if success, return the address with src last found in dst
*          if fail, return nullptr
*/
CAPI char* xstrrstr(const char *dst, const char *src);


/***
* @function
*          xstrchr()
* @param
*          dst - the destination buffer
*          val - look for character
* @return
*          if success, return the first find val 's address.
*          if fail, return nullptr
*/
CAPI char* xstrchr(const char *dst, char val);


/***
* @function
*          xstrrchr()
* @param
*          dst - the destination buffer
*          val - look for character
* @return
*          if success, return the last find val 's address.
*          if fail, return nullptr
*/
CAPI char* xstrrchr(char *dst, char val);


/***
* @function
*          xstrcpy_s()
* @param
*          dst  - the destination buffer
*          size - the destination buffer size
*          src  - the source buffer
* @return
*          if success, return dst addr
*          if fail, return nullptr
*/
CAPI char* xstrcpy_s(char *dst, unsigned size, const char *src);


/***
* @function
*          xstrcat_s()
* @param
*          dst  - the destination buffer
*          size - the destination buffer size
*          src  - the source buffer
* @return
*          if success, return dst addr
*          if fail, return nullptr
*/
CAPI char* xstrcat_s(char *dst, unsigned size, const char *src);


/***
* @function
*          xstrcmp_s()
* @param
*          src1 - the src1 buffer
*          src2 - the src2 buffer
*          n    - compare number
* @return
*          src1 < src2, return -1
*          src1 = src2, return 0
*          src1 > src2, return 1
*/
CAPI int xstrcmp_s(const char *src1, const char *src2, unsigned n);


#endif //_XSTRING_H_