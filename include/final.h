/** 
 * @brief It defines the final functions
 * @file final.h
 * @author Eric Morales
 * @version 1.0 
 * @date 23-04-2018
 * @copyright GNU Public License
 */

#ifndef __MENU__
#define __MENU__

/*Own libraries*/
#include "../include/types.h"

/**
 * @brief               It holds the necessary data to manage a Final.
 */
typedef struct _Final Final;

/**
 * @name 		final_create
 * @author 		Eric Morales
 * @version             1.0
 * @date		23-04-2018
 * @brief               It allocates memory for a Final we will be using to print.
 * @return		A Final.
 */
Final *final_create();

/**
 * @name 		final_destroy
 * @author 		Eric Morales
 * @version             1.0
 * @date		23-04-2018
 * @brief               It frees the memory a Final was allocating.
 * @param               Final* -> a final to be freed.
 * @return		A void.
 */
void final_destroy(Final *final);

/** 
 * @name 		final_paint
 * @author 		Eric Morales.
 * @version             1.0
 * @date		23-04-2018
 * @brief               It paints the game on the screen with all its info.
 * @param               Final* -> a final that will define where to print.
 * @return		A void.
 */
void final_paint(Final *final, RULES_STATUS rule);


#endif
