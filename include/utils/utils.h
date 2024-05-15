/**
 * @file template.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef UTILS_H
#define UTILS_H

/* -------------------------------- Includes -------------------------------- */

#include <stdint.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
char* floatToStr(float num, char* str);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
float strToFloat(unsigned char *str, uint16_t size);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
int16_t strToInt(unsigned char *str, uint16_t size);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
uint16_t  strToHex(unsigned char *str, uint16_t size);

#endif // UTILS_H

/* ------------------------------- End of file ------------------------------ */
