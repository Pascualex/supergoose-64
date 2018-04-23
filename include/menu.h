/** 
 * @brief It defines the menu functions
 * @file menu.h
 * @author Eric Morales
 * @version 1.0 
 * @date 23-04-2018
 * @updated 23-04-2018
 * @copyright GNU Public License
 */

#ifndef __MENU__
#define __MENU__

/*C libraries*/
#include <stdio.h>
/*Own libraries*/
#include "../include/types.h"

/**
 * @brief               It holds the necessary data to manage a Menu.
 */
typedef struct _Menu Menu;

/**
 * @name 		menu_create
 * @author 		Eric Morales
 * @version             1.0
 * @date		23-04-2018
 * @brief               It allocates memory for a Menu we will be using to print.
 * @return		A Menu.
 */
Menu* menu_create();

/**
 * @name 		menu_destroy
 * @author 		Eric Morales
 * @version             1.0
 * @date		23-04-2018
 * @brief               It frees the memory a Menu was allocating.
 * @param               Menu* -> a menu to be freed.
 * @return		A void.
 */
void menu_destroy(Menu *ge);

/** 
 * @name 		menu_paint
 * @author 		Eric Morales.
 * @version             1.0
 * @date		23-04-2018
 * @brief               It paints the game on the screen with all its info.
 * @param               Menu* -> a menu that will define where to print.
 * @return		A void.
 */
void menu_paint(Menu *menu);


#endif
