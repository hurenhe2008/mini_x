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
    char v = ch & 0xFF;  //truncate

    if (!d || !n) {
        return nullptr;
    }

    while (n--) {
        d[n] = v;
    }

    return dst;
}


void* xmemcpy(void *dst, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;

    if (!d || !s || !n) {
        return nullptr;
    }

    while (n--) {
        d[n] = s[n];
    }

    return dst;
}


void* xmemmove(void *dst, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;
    unsigned i = n;

    if (!d || !s || !n) {
        return nullptr;
    } 

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

    if (!d || !s || 0 == n) {
        return -1;
    }

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

    if (!d || !s || !size || !n || (size < n)) {
        return -1;
    }

    while (n--) {
        d[n] = s[n];
    }

    return 0;

}


int xmemmove_s(void *dst, unsigned size, const void *src, unsigned n)
{
    const char *s = (const char *)src;
    char *d = (char *)dst;
    unsigned i = n;

    if (!d || !s || !size || !n || (size < n)) {
        return -1;
    }

    if (s > d) {
        while (i--) {
            d[n - i - 1] = s[n - i - 1];
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