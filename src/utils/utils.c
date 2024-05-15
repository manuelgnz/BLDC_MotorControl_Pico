/**
 * @file template.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <utils.h>
#include <stdio.h>
#include <string.h>

/* ------------------------------- Public code ------------------------------ */

//TODO: documentar bien
/**********************************************************************************************************************
 * Returns a string with the float number passed by argument.
 *
 * @param num float number
 * @param str char pointer to a string where the function returns the result
 * @see strToFloat()
 *
 * @return string with the float number
 **********************************************************************************************************************/
char* floatToStr(float num, char* str) {
    memset((uint16_t*)str, 0, 10);
    char *tmpSign = (num < 0) ? "-" : "";
    float tmpVal = (num < 0) ? -num : num;

    int16_t tmpInt1 = tmpVal;                  // Get the integer (678).
    float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
    int16_t tmpInt2 = tmpFrac * 10000;  // Turn into integer (123).

    // Print as parts, note that you need 0-padding for fractional bit.

    sprintf(str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
    //strcpy(str, "2.5760");

    return str;
}

/**********************************************************************************************************************
 * Returns a float number parsing the string passed by argument.
 *
 * @param str char pointer to a string with the number
 * @param size length of the string
 * @see floatToStr(), strToInt()
 *
 * @return float number
 **********************************************************************************************************************/
float strToFloat(unsigned char *str, uint16_t size)
{
    int32_t len=0, n=0, i=0;
    float f=1.0, val=0.0, sign=1.0;
    str[size] = 0;

    // Minus sign
    if(str[0]=='-') {
        sign = -1;
        str++;
    }
    // Counts length of String
    while(str[len])len++;

    // Checks valid string
    if(!len) return 0;
    for(int i=0; i<len; i++) {
        if(str[i]!='.' && (str[i]<'0' || str[i]>'9')) return 0;
    }

    // Extracts Integer part
    while(i<len && str[i]!='.')
        n = 10*n + (str[i++]-'0');

    //checking if only Integer
    if(i==len) return n*sign;
    i++;
    while(i<len) {
        f*=0.1f;
        int32_t aux = str[i++] -'0';
        float aux2 = (float)aux;
        val+=(f*aux2);
    }
    return((val+n)*sign);
}

/**********************************************************************************************************************
 * Returns a integer number parsing the string passed by argument.
 *
 * @param str char pointer to a string with the number
 * @param size length of the string
 * @see strToFloat()
 *
 * @return integer number
 **********************************************************************************************************************/
int16_t strToInt(unsigned char *str, uint16_t size) {
    int16_t len=0, n=0, i=0;
    int16_t sign=1;
    //str[size] = 0;

    // Minus sign
    if(str[0]=='-') {
        sign = -1;
        str++;
        len = size-1;
    } else {
        len = size;
    }

    // Counts length of String
    //while(str[len])len++;

    // Checks valid string
    if(!len) return 0;
    for(int i=0; i<len; i++) {
        if(str[i]<'0' || str[i]>'9') return 0;
    }

    //Extracts Integer part
    while(i<len)
        n= 10*n + (str[i++] -'0');
    return(n*sign);
}

/**********************************************************************************************************************
 * Returns a integer number parsing the string passed by argument.
 *
 * @param str char pointer to a string with the number in hexadecimal format
 * @param size length of the string
 * @see strToFloat()
 *
 * @return integer number
 **********************************************************************************************************************/
uint16_t  strToHex(unsigned char *str, uint16_t size) {
    uint16_t ret = 0;
    for(int i=0; i<size; i++) {
        if(i!=0) ret <<= 4;
        if(str[i] >= '0' && str[i] <= '9') {
            ret |= (str[i]-'0');
        } else if (str[i] >= 'A' && str[i] <= 'F') {
            ret |= (str[i]-'A'+10);
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            ret |= (str[i]-'a'+10);
        } else return 0;
    }

    return ret;
}

/* ------------------------------- End of file ------------------------------ */
