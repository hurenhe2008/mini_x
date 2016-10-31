/************************************************************************
*                                                                       *
* author:   hurenhe   @  MPRTimes Co.                                   *
* date:     2016/07/14                                                  *
*                                                                       *
* declare:  mini_encode include the function declaration, provide like  *
*           as utf8¡¢base64 encode and decode, and code format convert. *
*                                                                       *
/***********************************************************************/
#ifndef __MINI_ENCODE_H__
#define __MINI_ENCODE_H__


/**
* utf8  <-->  unicode(UCS2)
**/
bool utf8_to_unicode(const char *utf8, unsigned utf8len, char *uni, unsigned unilen);
bool unicode_to_utf8(const char *uni, unsigned unilen, char *utf8, unsigned utf8len);


/**
* unicode(UCS2)  <-->  gbk 
**/
bool unicode_to_gbk(const char *uni, unsigned unilen, char *gbk, unsigned gbklen);
bool gbk_to_unicode(const char *gbk, unsigned gbklen, char *uni, unsigned unilen);


/**
* utf8 <--> gbk
**/
bool utf8_to_gbk(const char *utf8, unsigned utf8len, char *gbk, unsigned gbklen);
bool gbk_to_utf8(const char *gbk, unsigned gbklen, char *utf8, unsigned utf8len);


/**
* @function:  utf8 encode / decode
*
* @param:    [in] is the be converted input data
*            [out] is the be converted to output data
*
* @return:   >0   means the outbuf valid byte length
*             0   means params error
*            -1   means output buffer length too short
*            -2   means input data byte format error
*
* @note:     unicode is little-endian encode.
*
**/

/* unicode --> utf8  [0000 - FFFF]*/
int utf8_encode(const unsigned char *in, unsigned inlen,    
    unsigned char *out, unsigned outlen);
/* multibyte --> utf8  [0 - FFFF]*/
int utf8_encode_m(const unsigned char *in, unsigned inlen,  
    unsigned char *out, unsigned outlen);
/* utf8 --> unicode  [0000 - FFFF]*/
int utf8_decode(const unsigned char *in, unsigned inlen,    
    unsigned char *out, unsigned outlen);
/* utf8 --> multibyte  [0 - FFFF]*/
int utf8_decode_m(const unsigned char *in, unsigned inlen,  
    unsigned char *out, unsigned outlen);


/**
* @function: base64_encode / base64_decode
*
* @param:    [in] is the be converted input data,
*            [out] is the be converted to output data,  
*
* @return:   >0   means the outbuf valid byte length
*             0   means params error
*            -1   means output buffer length too short
*            -2   means input data byte format error
**/
int base64_encode(const unsigned char *in, unsigned inlen, 
    unsigned char *out, unsigned outlen);
int base64_decode(const unsigned char *in, unsigned inlen, 
    unsigned char *out, unsigned outlen);

#endif //__MINI_ENCODE_H__