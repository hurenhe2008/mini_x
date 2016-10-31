#include "mini_encode.h"
#include <string.h>

/*************************************************************
* 说明：                                                     *
*                                                            *
* 3个字符用4个base64字符表示                                  *
* 00xxxxxx 可表示 2^6 = 64 字符， 全部用打印字符转码           *
* 00xxxxxx 中低六位的数值 对应base64char数组的下标             *
* 不足3个字符的用0补全某一个不足6位， 和 = 字符填充第3/4个字符  *
*                                                            *
*************************************************************/

/*********************************************************************************************/

/*condition: (len % 3) == 1 / len = 1                                                        */
/*                                                                                           */
/*                       0xaaaaaaaa                                                          */
/*                           |                                                               */
/*                           V                                                               */
/*         0x00aaaaaa               0x00aa0000                                               */
/*              |                        |                                                   */
/*              V                        V                                                   */
/*   base64char[0x00aaaaaa]    base64char[0x00aa0000]           '='          '='             */
/*                                                                                           */
/*                                                                                           */

/**************************************************************************************************/

/*condition: (len % 3) == 2 / len = 2                                                             */
/*                                                                                                */
/*                       0xaaaaaaaa              0xbbbbbbbb                                       */
/*                           |                       |                                            */
/*                           V                       V                                            */
/*         0x00aaaaaa               0x00aabbbb              0x00bbbb00                            */
/*              |                        |                       |                                */
/*              V                        V                       V                                */
/*    base64char[0x00aaaaaa]   base64char[0x00aabbbb]  base64char[0xbbbb0000]        '='          */
/*                                                                                                */

/*******************************************************************************************************/

/*condition: (len % 3) == 0 / len = 3   (len > 0)                                                      */
/*                                                                                                     */
/*                      0xaaaaaaaa              0xbbbbbbbb              0xcccccccc                     */
/*                          |                       |                        |                         */
/*                          V                       V                        V                         */
/*         0x00aaaaaa               0x00aabbbb              0x00bbbbcc              0x00cccccc         */
/*              |                       |                        |                       |             */
/*              V                       V                        V                       V             */
/*    base64char[0x00aaaaaa]  base64char[0x00aabbbb]  base64char[0x00bbbbcc]  base64char[0x00cccccc]   */
/*                                                                                                     */




/* base64 char array */ 
static const char base64char[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  


int base64_encode(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    if (!in || 0 == inlen || !out) {
        return 0;
    }

    if (inlen % 3 != 0) {
        if (outlen < (inlen / 3 + 1) * 4) {
            return -1;
        }
    }
    else {
        if (outlen < (inlen / 3) * 4) {
            return -1;
        }
    }

    /*sequence parse*/
    unsigned i, pos;
    unsigned char curr = 0;

    for (i = 0, pos = 0; i < inlen; i += 3) {

        curr = in[i] >> 2;   /* 0xaaaaaaaa >> 2 --> 0x00aaaaaa*/
        curr &= 0x3F;        

        out[pos++] = base64char[curr];  /* 0x00aaaaaa */

        curr = (in[i] & 0x03) << 4;     
        curr &= 0x30;       /*0x00aa0000*/

        if ((i + 1) < inlen) {
            curr |= (in[i + 1] >> 4) & 0x0F;     /*0x00aa0000 | 0x0000bbbb -> 0x00aabbbb*/ 
            out[pos++] = base64char[curr];
        }
        else {
            out[pos++] = base64char[curr];  /*0x00aa0000*/
            out[pos++] = '=';
            out[pos++] = '=';
            break;
        }
        
        curr = ((in[i + 1] & 0x0F) << 2);
        curr &= 0x3C;       /*0x00bbbb00*/

        if ((i + 2) < inlen) {
            curr |= (in[i + 2] >> 6) & 0x03;    /*0x00bbbb00 | 0x000000cc -> 0x00bbbbcc*/
            out[pos++] = base64char[curr];
        }
        else {
            out[pos++] = base64char[curr]; /*0x00bbbb00*/
            out[pos++] = '=';
            break;
        }

        curr = (in[i + 2] & 0x3F);  /*0x00cccccc*/
        out[pos++] = base64char[curr];
    }

    return pos;
}


static unsigned char find_pos_in_base64_array(unsigned char value);

int base64_decode(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    if (!in || 0 == inlen || (inlen & 0x03) != 0 || !out) {
        return 0;
    }

    if (outlen <= ((inlen >> 2) - 1) * 3) {
        return -1;
    }
    
    unsigned i, pos;
    unsigned char tmp[4] = { 0 };  /*save 4 byte for parse*/

    for (i = 0, pos = 0; i < inlen; i += 4) {
        if ((tmp[0] = find_pos_in_base64_array(in[i])) >= 64 ||      /*not = and other*/
            (tmp[1] = find_pos_in_base64_array(in[i + 1])) >= 64 ||  /*not = and other*/
            (tmp[2] = find_pos_in_base64_array(in[i + 2])) > 64 ||   /*not other*/
            (tmp[3] = find_pos_in_base64_array(in[i + 3])) > 64) {   /*not other*/
            return -2;
        }

        if (pos >= outlen) {   /*detect*/
            break;
        }
        out[pos++] = ((tmp[0] << 2) & 0xFC) | ((tmp[1] >> 4) & 0x03);

        if ('=' == in[i + 2]) {
            break;
        }

        if (pos >= outlen) {   /*detect*/
            break;
        }
        out[pos++] = ((tmp[1] << 4) &0xF0) | ((tmp[2] >> 2) & 0x0F);

        if ('=' == in[i + 3]) {
            break;
        }

        if (pos >= outlen) {   /*detect*/
            break;
        }
        out[pos++] = ((tmp[2] << 6) & 0xC0) | (tmp[3] & 0x3F);
    }
    
    return pos;
}

static unsigned char find_pos_in_base64_array(unsigned char value)
{
    unsigned char pos = 0;
    if (value >= 97 && value <= 122) {  /*a-z*/
        pos = value - 71;
    }
    else if (value >= 48 && value <= 57) {  /*0-9*/
        pos = (value - '0') + 52;
    }
    else if (value >= 65 && value <= 90) {  /*A-Z*/
        pos = value - 65;
    }
    else if ('+' == value) {  /*+*/
        pos = 62;
    }
    else if ('/' == value) {  /*/*/
        pos = 63;
    }
    else if('=' == value){  /*=*/
        pos = 64;  
    }
    else {  /*error*/
        pos = 65;
    }

    return pos;
}