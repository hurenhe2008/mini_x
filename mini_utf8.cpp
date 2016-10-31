#include "mini_encode.h"
#include <string.h>

/*****************************************************************************************************
*  傍苧��                                                    
*                                                         
*  utf8恷海俶勣6倖忖准燕幣匯倖忖憲�� 嶄猟匯違3倖忖准燕幣     
*
*  
*     UNICODE/UCS-4   |      bit       |       utf-8       |      utf8_bit     |      remark                  
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！            
*                     |                |                   |                   |
*      0000 - 007F    |      0-7       |     0XXXXXXX      |         1         |      AscII
*                     |                |                   |                   |              
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！
*                     |                |                   |                   |
*      0080 - 07FF    |      8-11      |     110XXXXX      |         2         |
*                     |                |     10XXXXXX      |                   |
*                     |                |                   |                   |
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！
*                     |                |                   |                   |
*      0800 - FFFF    |     12-16      |     1110XXXX      |         3         | 児云袈律: 0-FFFF
*                     |                |     10XXXXXX      |                   | 嶄猟脅壓緩袈律
*                     |                |     10XXXXXX      |                   |
*                     |                |                   |                   |
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！
*                     |                |                   |                   |
*    10000 - 1FFFFF   |     17-21      |     11110XXX      |         4         | Unicode6.0袈律��
*                     |                |     10XXXXXX      |                   |  0 - 10FFFF
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |                   |                   |
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！
*                     |                |                   |                   |
*  200000 - 3FFFFFF   |     22-26      |     111110XX      |         5         | 
*                     |                |     10XXXXXX      |                   |  
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |                   |                   |
*  ！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！！|！！！！！！！！！！！！！！！！！！
*                     |                |                   |                   |
*  400000 - 7FFFFFFF  |     27-31      |     1111110X      |         6         | UCS-4
*                     |                |     10XXXXXX      |                   |  
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |     10XXXXXX      |                   |
*                     |                |                   |                   |
******************************************************************************************************/

/***************************************
*
*        AscII    [0-127]
*
*        UNICODE  [0000-FFFF] 
* 
*        GBK      [8140-FEFE]
*
*        GB2312   [A1A1-FEFE]
*
***************************************/

static unsigned char count_char_have_bytes(unsigned char startbyte);




/* unicode --> utf8 */
int utf8_encode(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    /*inlen must be even number*/
    if (!in || 0 == inlen || (inlen & 0x02) != 0 || !out || 0 == outlen) { 
        return 0;
    }

    unsigned pos = 0;

    for (unsigned i = 0; i < inlen; i += 2) {

        if (in[i + 1] == 0) { /*AscII*/   /*high byte is 0*/
            if (pos >= outlen) {
                return -1;
            }
            out[pos++] = in[i];  /*little-endian*/
            continue;
        }
        
        /*Other Char*/
        if (pos >= outlen) {
            return -1;
        }
        out[pos] = 0xE0;             /*1110 0000*/
        out[pos++] |= (in[i] >> 4);  /*1110 XXXX*/

        if (pos >= outlen) {
            return -1;
        }
        out[pos] = 0x80;                     /*1000 0000*/
        out[pos] |= ((in[i] & 0x0F) << 2);   /*10XX XX00*/
        out[pos++] |= (in[i + 1] >> 6);      /*10XX XXXX*/

        if (pos >= outlen) {
            return -1;
        }

        out[pos] = 0x80;                     /*1000 0000*/
        out[pos++] |= (in[i + 1] & 0x3F);    /*10XX XXXX*/
    }

    return pos - 1;
}


/* multibyte --> utf8 */
int utf8_encode_m(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    if (!in || 0 == inlen || !out || 0 == outlen) {
        return 0;
    }

    unsigned pos = 0;
    for (unsigned i = 0; i < inlen; ) {

        /*AscII*/
        if (in[i] <= 127) {
            if (pos >= outlen) {
                return -1;
            }
            out[pos++] = in[i];
            i += 1;
            continue;
        }

        /*>127, maybe GBK/GB2312 [0x8000-0xFFFF]*/
        if (pos >= outlen) {
            return -1;
        }
        out[pos] = 0xE0;             /*1110 0000*/
        out[pos++] |= (in[i] >> 4);  /*1110 XXXX*/

        if (pos >= outlen) {
            return -1;
        }
        out[pos] = 0x80;                     /*1000 0000*/
        out[pos] |= ((in[i] & 0x0F) << 2);   /*10XX XX00*/
        out[pos++] |= (in[i + 1] >> 6);      /*10XX XXXX*/

        if (pos >= outlen) {
            return -1;
        }

        out[pos] = 0x80;                     /*1000 0000*/
        out[pos++] |= (in[i + 1] & 0x3F);    /*10XX XXXX*/
        i += 2;
    }

    return pos;
}


/* utf8 --> unicode */
int utf8_decode(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    if (!in || 0 == inlen || !out || 0 == outlen) {
        return 0;
    }

    unsigned char char_byte_cnt = 0;
    unsigned char left_valid_bit = 0;
    unsigned char left_need_bit = 0;
    unsigned pos = 0, inner_pos = 0;

    for (unsigned i = 0; i < inlen; i += char_byte_cnt) {

        char_byte_cnt = count_char_have_bytes(in[i]);

        if ((char_byte_cnt > 6) || (i + char_byte_cnt >= inlen)) {
            return -2;
        }

        /* AscII */
        if (1 == char_byte_cnt) {  /*AscII:  0XXXXXXXX*/
            if (pos >= outlen || (pos + 1) >= outlen) {
                return -1;
            }

            out[pos++] = in[i];    /*little-endian*/
            out[pos++] = '\0';    
            continue;
        }

        /* not AscII */
        if (pos >= outlen) {
            return -1;
        }

        inner_pos = 0;

        left_valid_bit = 8 - (char_byte_cnt + 1);   /*1 is bit 0*/
        out[pos] = in[i + inner_pos] << (8 - left_valid_bit);   /*eg: 1110XXXX*/
        left_need_bit = 8 - left_valid_bit;
        left_valid_bit = 0;

        ++inner_pos;
        while (inner_pos < char_byte_cnt) {

            if ((in[i + inner_pos] & 0xC0) != 0x80) {  /*0x10XXXXXX check*/
                return -2;
            }

            if (0 == left_need_bit) {

                ++pos;                 /*pad 8 bit, next pad char*/

                if (pos >= outlen) {   /*out buffer length is too short*/
                    return -1;
                }

                if (0 != left_valid_bit) {
                    out[pos] = (in[i + inner_pos] << (8 - left_valid_bit));
                    left_need_bit = 8 - left_valid_bit;
                    left_valid_bit = 0;
                }
                else {     /*0x111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX*/
                    out[pos] = (in[i + inner_pos] << 2);
                    left_need_bit = 2;
                    left_valid_bit = 0;
                }
            }
            else if (left_need_bit <= 6) {  /*0x10XXXXXX*/
                left_valid_bit = 6 - left_need_bit;
                out[pos] |= ((in[i + inner_pos] & 0x3F) >> left_valid_bit);
                left_need_bit = 0;
            }
            else if (7 == left_need_bit){
                left_valid_bit = 0;
                out[pos] |= ((in[i + inner_pos] & 0x3F) << 1);
                left_need_bit -= 6;
            }
            else {
                return -2;
            }

            if (0 == left_valid_bit) {    /*not left, next byte*/
                ++inner_pos;
            }
        }

        ++pos;  //next pos
    }

    return pos;
}

/* utf8 --> multibytes */
int utf8_decode_m(const unsigned char *in, unsigned inlen,
    unsigned char *out, unsigned outlen)
{
    memset(out, 0, outlen);

    if (!in || 0 == inlen || !out || 0 == outlen) {
        return 0;
    }

    unsigned char char_byte_cnt = 0;
    unsigned char left_valid_bit = 0;
    unsigned char left_need_bit = 0;
    unsigned pos = 0, inner_pos = 0;

    for (unsigned i = 0; i < inlen;  i += char_byte_cnt) {
    
        char_byte_cnt = count_char_have_bytes(in[i]);

        if ((char_byte_cnt > 6) || (i + char_byte_cnt > inlen)) { /*not  >= inlen*/
            return -2;
        }
       
        /* AscII */
        if (1 == char_byte_cnt) {  /*AscII:  0XXXXXXXX*/  
            if (pos >= outlen) {
                return -1;
            }

            out[pos++] = in[i];
            continue;
        }

        /* not AscII */
        inner_pos = 0;

        left_valid_bit = 8 - (char_byte_cnt + 1);   /*1 is bit 0*/ 
        out[pos] = in[i + inner_pos] << (8 - left_valid_bit);   /*eg: 1110XXXX*/
        left_need_bit = 8 - left_valid_bit;
        left_valid_bit = 0;

        ++inner_pos;
        while (inner_pos < char_byte_cnt) {

            if ((in[i + inner_pos] & 0xC0) != 0x80) {  /*0x10XXXXXX check*/
                return -2;
            }

            if (0 == left_need_bit) {
                ++pos;         /*pad 8 bit, next pad char*/

                if (pos >= outlen) {   /*out buffer length is too short*/
                    return -1;
                }

                if (0 != left_valid_bit) {  
                    out[pos] = (in[i + inner_pos] << (8 - left_valid_bit));
                    left_need_bit = 8 - left_valid_bit;
                    left_valid_bit = 0;
                }
                else {     /*0x111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX*/
                    out[pos] = (in[i + inner_pos] << 2);
                    left_need_bit = 2;
                    left_valid_bit = 0;
                }    
            }
            else if (left_need_bit <= 6) {  /*0x10XXXXXX*/
                left_valid_bit = 6 - left_need_bit;
                out[pos] |= ((in[i + inner_pos] & 0x3F) >> left_valid_bit);
                left_need_bit = 0;
            }
            else if (7 == left_need_bit){
                left_valid_bit = 0;
                out[pos] |= ((in[i + inner_pos] & 0x3F) << 1);
                left_need_bit -= 6;
            }
            else {
                return -2;
            }
            
            if (0 == left_valid_bit) {    /*not left, next byte*/
                ++inner_pos;
            }   
        }

        ++pos;  //next pos
    }

    return pos;
}

static unsigned char count_char_have_bytes(unsigned char startbyte)
{
    unsigned char bit_1_cnt = 0;

    while (bit_1_cnt <= 6) {

        if (0 == (startbyte & (0x80 >> bit_1_cnt))) {
            break;
        }
        
        ++bit_1_cnt;
    }

    if ((6 == bit_1_cnt && 1 == (startbyte & 0x02))  /*0x1111111X*/  
        || (1 == bit_1_cnt)) {  /*0x10XXXXXX*/

        bit_1_cnt = 8;    /*error flag*/

    }

    return (0 == bit_1_cnt) ? 1 : bit_1_cnt;
}