/** 
 * @brief It defines the menu functions
 * @file menu.c
 * @author Eric Morales
 * @version 1.0 
 * @date 23-04-2018
 * @updated 23-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
/*Own libraries*/
#include "../include/screen.h"
#include "../include/menu.h"

/*Menu structure, which includes the seven areas (options).*/
struct _Menu {
    Area *title, *new, *load, *guide, *terms, *options, *exit;
};

/*This function is used to allocate the memory the menu is going to use.*/
Menu *menu_create() {
    Menu *menu = NULL;

    screen_init(BLACK);
    menu = (Menu *) malloc(sizeof (Menu));

	menu->title =   screen_area_init(  2,  2, 77, 21, GREEN, BLACK, FALSE);
    menu->new =     screen_area_init( 25, 27, 30,  1,  BLUE, BLACK,  TRUE);
    menu->load =    screen_area_init( 25, 29, 30,  1,  BLUE, BLACK,  TRUE);
    menu->guide =   screen_area_init( 25, 31, 30,  1,  BLUE, BLACK,  TRUE);
    menu->terms =   screen_area_init( 25, 33, 30,  1,  BLUE, BLACK,  TRUE);
    menu->options = screen_area_init( 25, 35, 30,  1,  BLUE, BLACK,  TRUE);
    menu->exit =    screen_area_init( 25, 37, 30,  1,  BLUE, BLACK,  TRUE);

    return menu;
}

/*This function is used to free all the memory used by the menu*/
void menu_destroy(Menu *menu) {

    if (menu == NULL) return;

	screen_area_destroy(menu->title);
    screen_area_destroy(menu->new);
    screen_area_destroy(menu->load);
    screen_area_destroy(menu->guide);
    screen_area_destroy(menu->terms);
    screen_area_destroy(menu->options);
    screen_area_destroy(menu->exit);

    free(menu);
}

/*This function is the one responsible of painting the menu*/
void menu_paint(Menu *menu, int position) {
    wchar_t unicode_str[80];

    /* Paint the in the title area */
	screen_area_clear(menu->title);
    swprintf(unicode_str, COLUMNS, L"    _____                        ______                         _____ __ __");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   / ___/ __  ______  ___  _____/ ____/___  ____  ________     / ___// // /");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   \\__  \\/ / / / __ \\/ _ \\/ ___/ / __/ __ \\/ __ \\/  ___/_ \\   / __ \\/ // /_");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   ___/ / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ (__  )  __/  / /_/ /__  __/");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"  /____/\\____/ ____/\\___/_/   \\____/\\____/\\____/____/\\__/____\\____/  /_/");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"            /_/                                         /___/");
    screen_area_puts(menu->title, unicode_str);

    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(menu->title, unicode_str);

    swprintf(unicode_str, COLUMNS, L"                                                             /\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                                            /  \\  /\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                ___________________      /\\/    \\/  \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                       /\\      /\\        ______    \\    /   /\\/\\  /\\/\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                      /  \\    //_\\       \\    /\\    \\  /\\/\\/    \\/    \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"               /\\    / /\\/\\  //___\\       \\__/  \\    \\/");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"              /  \\  /\\/    \\//_____\\       \\ |[]|     \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"             /\\/\\/\\/       //_______\\       \\|__|      \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"            /      \\      /XXXXXXXXXX\\                  \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                    \\    /_I_II  I__I_\\__________________\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           I_I|  I__I_____[]_|_[]_____I");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           I_II  I__I_____[]_|_[]_____I");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           I II__I  I     XXXXXXX     I");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    screen_area_puts(menu->title, unicode_str);




/*
                                                 /\
                                                /  \  /\
                    ___________________      /\/    \/  \
           /\      /\        ______    \    /   /\/\  /\/\
          /  \    //_\       \    /\    \  /\/\/    \/    \
   /\    / /\/\  //___\       \__/  \    \/
  /  \  /\/    \//_____\       \ |[]|     \
 /\/\/\/       //_______\       \|__|      \
/      \      /XXXXXXXXXX\                  \
        \    /_I_II  I__I_\__________________\
               I_I|  I__I_____[]_|_[]_____I
               I_II  I__I_____[]_|_[]_____I
               I II__I  I     XXXXXXX     I
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/

	screen_color_box(24, 26, 32, 13, WHITE, BLACK);
	screen_color_box(25, 27+position*2, 30, 1, YELLOW, BLACK);	

	screen_area_clear(menu->new);
	swprintf(unicode_str, COLUMNS, L"NEW GAME");
	screen_area_puts(menu->new, unicode_str);

	screen_area_clear(menu->load);
	swprintf(unicode_str, COLUMNS, L"LOAD GAME");
	screen_area_puts(menu->load, unicode_str);

	screen_area_clear(menu->guide);
	swprintf(unicode_str, COLUMNS, L"Guide and controls");
	screen_area_puts(menu->guide, unicode_str);

	screen_area_clear(menu->terms);
	swprintf(unicode_str, COLUMNS, L"Terms of use");
	screen_area_puts(menu->terms, unicode_str);

	screen_area_clear(menu->options);
	swprintf(unicode_str, COLUMNS, L"Options");
	screen_area_puts(menu->options, unicode_str);

	screen_area_clear(menu->exit);
	swprintf(unicode_str, COLUMNS, L"EXIT");
	screen_area_puts(menu->exit, unicode_str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}
