#include "mini_encode.h"

#include <stdio.h>
#include <string.h>


bool utf8_to_unicode(const char *utf8, unsigned utf8len, char *uni, unsigned unilen)
{
    memset(uni, 0, unilen);

    if (!utf8 || 0 == utf8len) {
        return false;
    }



    return false;
}

bool unicode_to_utf8(const char *uni, unsigned unilen, char *utf8, unsigned utf8len)
{
    memset(utf8, 0, utf8len);

    if (!uni || 0 == unilen) {
        return false;
    }



    return false;
}

bool unicode_to_gbk(const char *uni, unsigned unilen, char *gbk, unsigned gbklen)
{
    memset(gbk, 0, gbklen);
    
    if (!uni || 0 == unilen) {
        return false;
    }


    return false;
}

bool gbk_to_unicode(const char *gbk, unsigned gbklen, char *uni, unsigned unilen)
{
    memset(uni, 0, unilen);

    if (!gbk || 0 == gbklen) {
        return false;
    }


    return false;
}

bool utf8_to_gbk(const char *utf8, unsigned utf8len, char *gbk, unsigned gbklen)
{
    memset(gbk, 0, gbklen);

    if (!utf8 || 0 == utf8len) {
        return false;
    }


    return false;
}

bool gbk_to_utf8(const char *gbk, unsigned gbklen, char *utf8, unsigned utf8len)
{
    memset(utf8, 0, utf8len);

    if (!gbk || 0 == gbklen) {
        return false;
    }


    return false;
}



