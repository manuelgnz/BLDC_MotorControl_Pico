/**
 * @file foc.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef FOC_H
#define FOC_H

/* -------------------------------- Includes -------------------------------- */

/* -------------------------- Constants and macros -------------------------- */

/** FOC frequency. */
#define FOC_FREQUENCY   20

/** FOC period in us. */
#define FOC_PERIOD      ((1.0f/((float)FOC_FREQUENCY))*1000.0f)

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief FOC.
 */
void foc(void);

#endif // FOC_H

/* ------------------------------- End of file ------------------------------ */
