#include "xstring.h"


//=================================================================================================================
/*                                dst and src address layout
                             
  [little endian] <----------s----------> <----------d----------> [big endian]   (s < d and not related)

  [little endian]     <----------s----<=====>----d---------->     [big endian]   (s's end part in d's start part)   

  [little endian]            <----------s/d---------->            [big endian]   (s and d address equal)

  [little endian]     <----------d----<=====>----s---------->     [big endian]   (s'start part in d's end part)

  [little endian] <----------d----------> <----------s----------> [big endian]   (s > d and not related)

*/
//==================================================================================================================

/*compatible with C compile*/
#ifndef NULL
#define NULL (void *)0
#endif

#ifndef nullptr
#define nullptr NULL
#endif


void* xmemset(void *dst, int ch, unsigned n)
{
    char *d = (char *)dst;
    char v = ch & 0xFF;   /*truncate*/

    if (!d || !n) 
        return nullptr;

    while (n--) 
        d[n] = v;

    return dst;
}

void* xmemcpy(void *dst, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;

    if (!d || !s || !n) 
        return nullptr;

    while (n--) 
        d[n] = s[n];

    return dst;
}

void* xmemmove(void *dst, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;
    unsigned i = n;

    if (!d || !s || !n) 
        return nullptr;

    if (s > d) {
        while (i--) {
            d[n-i-1] = s[n-i-1];
        }
    }

    if (s < d) {
        while (i--) {
            d[i] = s[i];
        }
    }

    /*s == d, not handle*/
    return dst;
}

int xmemcmp(const void *dst, const void *src, unsigned n)
{
    const char *d = (const char *)dst;
    const char *s = (const char *)src;

    if (!d || !s || 0 == n) 
        return -1;

    while (n--) {
        if (d[n] != s[n]) {
            return -1;
        }
    }

    return 0;
}

int xmemcpy_s(void *dst, unsigned size, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;

    if (!d || !s || !size || !n) 
        return -1;

    n = (n > size) ? size : n;  /*if n > size, truncate*/

    while (n--) 
        d[n] = s[n];

    return 0;

}

int xmemmove_s(void *dst, unsigned size, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;
    unsigned i = n;

    if (!d || !s || !size || !n || (size < n)) 
        return -1;

    n = (n > size) ? size : n;  /*if n > size, truncate*/

    if (s > d) {
        while (i--) {
            d[n-i-1] = s[n-i-1];
        }
    }

    if (s < d) {
        while (i--) {
            d[i] = s[i];
        }
    }

    /*s == d, not handle*/
    return 0;
}



unsigned xstrlen(const char *src)
{
    unsigned cnt = 0;

    if (!src) 
        return cnt;

    while (*src++) 
        ++cnt;

    return cnt;
}

int xstrcmp(const char *src1, const char *src2)
{
    while (*src1 && *src2) {

        if (*src2 > *src1) return -1;

        if (*src2 < *src1) return 1;

        ++src1;  ++src2;
    }

    if (*src2 > *src1) return -1;

    if (*src2 < *src1) return 1;

    return 0;
}

char* xstrcpy(char *dst, const char *src)
{
    char *d = dst;

    if (!dst || !src) 
        return nullptr;

    while (*src) 
        *dst++ = *src++;

    *dst = '\0';

    return d;
}

char* xstrcat(char *dst, const char *src)
{
    char *d = dst;

    if (!dst || !src) 
        return nullptr;

    while (*dst) {
        dst = dst + 1;
    }

    while (*src) 
        *dst++ = *src++;

    *dst = '\0';

    return d;
}

char* xstrstr(const char *dst, const char *src)
{
    const char *s = src, *d = dst;
    unsigned dlen = 0, slen = 0;
    int gaplen = 0, i = 0, j = 0;

    if (!dst || !src || !*dst || !*src) 
        return nullptr;

    while (*s++)  ++slen;
    while (*d++)  ++dlen;
    
    if ((gaplen = dlen - slen) < 0)
        return nullptr;

    s = src;  

    for (i = 0; i <= gaplen; ++i) {

        d = dst + i;

        for (j = 0; j < slen; ++j) 
            if (d[j] != s[j]) 
                break;
                
        if (j == slen) return d;
    }

    return nullptr;
}

char* xstrrstr(char *dst, const char *src)
{
    const char *s = src, *d = dst;
    unsigned dlen = 0, slen = 0;
    int gaplen = 0, i = 0, j = 0;

    if (!dst || !src || !*dst || !*src) 
        return nullptr;

    while (*s++)  ++slen;
    while (*d++)  ++dlen;

    if ((gaplen = dlen - slen) < 0) 
        return nullptr;

    s = src;

    for (i = gaplen; i >= 0; --i) {

        d = dst + i;

        for (j = 0; j < slen; ++j)
            if (d[j] != s[j]) 
                break;

        if (j == slen) return d;
    }

    return nullptr;
}

char* xstrchr(const char *dst, char val)
{
    if (!dst)  return nullptr;

    while (*dst) {
        if (val == *dst) 
            return dst;
        ++dst;
    }

    if (val == *dst)  /*'\0'*/
        return dst;

    return nullptr;
}

char* xstrrchr(const char *dst, char val)
{
    unsigned dlen = 0;
    const char *d = dst;
    
    while (*dst++)   ++dlen;

    while (dst >= d) {
        if (val == *dst) return dst; /*include '\0'*/ 
        --dst;
    }
    
    return nullptr;
}

char* xstrcpy_s(char *dst, unsigned size, const char *src)
{
    unsigned i = 0;

    if (!dst || !src || !size || !*src)  
        return nullptr;

    while (*src && i < size) 
        dst[i++] = *src++;

    dst[i] = '\0';   /*i == size, copy and truncate*/

    return dst;
}

char* xstrcat_s(char *dst, unsigned size, const char *src)
{
    char *d = dst;
    unsigned i = 0, len = 0, left = 0;

    if (!dst || !src || !size) 
        return nullptr;

    while (*dst++)  ++len;

    if ((left = size - len) <= 0) 
        return nullptr;

    i = 0;
    while (*src && i < left) 
        dst[i++] = *src++;

    *dst = '\0';

    return d;
}

int xstrcmp_s(const char *src1, const char *src2, unsigned n)
{
    unsigned i = 0;

    if (!src1 || !src2 || !n) {
        return -2;
    }

    for (i = 0; i < n; ++i) {
        if (src2[i] > src1[i]) {
            return -1;
        }

        if (src2[i] < src1[i]) {
            return 1;
        }

        if (0 == src2[i]) { /*src1[i] == src2[i]: '\0'*/
            break;
        }
    }

    return 0;
}
