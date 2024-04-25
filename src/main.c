/**
 * @file main.c
 * @brief Main source file where the init and tasks take place.
 * 
 * @version aa
 * @date 25 Apr 2024
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <pico/stdlib.h>
#include <system.h>

/* -------------------------- Constants and macros -------------------------- */

/* ------------------------------- Public code ------------------------------ */

int main(void)
{
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    // gpio_init(23);
    // gpio_set_dir(23, GPIO_OUT);

    //Infinite loop
    while(1)
    {
        gpio_put(25, 1);
        sleep_ms(500);
        gpio_put(25,0);
        sleep_ms(500);

        // gpio_put(23, 1);
        // sleep_ms(10);
        // gpio_put(23,0);
        // sleep_ms(10);
    }    
}

/* ------------------------------- End of file ------------------------------ */
