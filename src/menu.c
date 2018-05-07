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

    menu->title =   screen_area_init(25,  6, 78, 34, GREEN, BLACK, FALSE);
    menu->new =     screen_area_init(49, 42, 30,  1,  BLUE, BLACK,  TRUE);
    menu->load =    screen_area_init(49, 44, 30,  1,  BLUE, BLACK,  TRUE);
    menu->guide =   screen_area_init(49, 46, 30,  1,  BLUE, BLACK,  TRUE);
    menu->terms =   screen_area_init(49, 48, 30,  1,  BLUE, BLACK,  TRUE);
    menu->options = screen_area_init(49, 50, 30,  1,  BLUE, BLACK,  TRUE);
    menu->exit =    screen_area_init(49, 52, 30,  1,  BLUE, BLACK,  TRUE);

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
    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(menu->title, unicode_str);


    swprintf(unicode_str, COLUMNS, L"                            _________-----_____");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                 _____------           __      ----_");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"           ___----             ___------             \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"             ----________        ----                 \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                         -----__    |             _____)");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                              __-                /     \\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                  _______-----    ___--          \\    /)\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"            ------_______      ---____            \\__/  /");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                         -----__    \\ --    _          /\\");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                     ----|   /          |");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  |___________|");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  | ((_(_)| )_)");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         |  \\_((_(_)|/(_)");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         \\             (");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                          \\_____________)");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                               /  (");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                      ((____.-'    )");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                       \\         /");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                        \\'-.-.-'`/");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                         \\______/");
    screen_area_puts(menu->title, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                                           _|_\\_");
    screen_area_puts(menu->title, unicode_str);



/*
                  _________-----_____
       _____------           __      ----_
___----             ___------              \
   ----________        ----                 \
               -----__    |             _____)
                    __-                /     \
        _______-----    ___--          \    /)\
  ------_______      ---____            \__/  /
               -----__    \ --    _          /\
                      --__--__     \_____/   \_/\
                              ----|   /          |
                                  |  |___________|
                                  |  | ((_(_)| )_)
                                  |  \_((_(_)|/(_)
                                  \             (
                                   \_____________)
                                        /  (
                               ((____.-'    )
                                \\         /
                                 \'-.-.-'`/
                                  \______/
                                    _|_\_
*/

    screen_color_box(48, 41, 32, 13, WHITE, BLACK);
    screen_color_box(49, 42+position*2, 30, 1, YELLOW, BLACK);  
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
    swprintf(unicode_str, COLUMNS, L"Documentation");
    screen_area_puts(menu->options, unicode_str);

    screen_area_clear(menu->exit);
    swprintf(unicode_str, COLUMNS, L"EXIT");
    screen_area_puts(menu->exit, unicode_str);

    /* Dump to the terminal */
    screen_paint();
}
