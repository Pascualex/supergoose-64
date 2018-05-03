/** 
 * @brief It defines the graphic engine functions
 * @file graphic_engine.c
 * @author
 * @version 1.0 
 * @date 06-04-2018
 * @updated 07-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/ 
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
/*Own libraries*/
#include "../include/screen.h"
#include "../include/graphic_engine.h"

/*Graphic Engine structure, which includes the six areas that are used when playing.*/
struct _Graphic_engine {
    Area *map, *descript, *banner, *help, *feedback, *chat;
};

/*This function is used to allocate the memory the graphic engine is going to use.*/
Graphic_engine *graphic_engine_create() {
    Graphic_engine *graphic_engine = NULL;

    screen_init(BLACK);
    graphic_engine = (Graphic_engine *) malloc(sizeof(Graphic_engine));

    graphic_engine->banner   = screen_area_init(  1,  0, 78,  6, GREEN, BLACK, FALSE);
    graphic_engine->map      = screen_area_init(  3,  7, 49, 23, BLUE,  BLACK,  TRUE);
    graphic_engine->descript = screen_area_init( 53,  7, 24, 23, WHITE, BLACK,  TRUE);
    graphic_engine->help     = screen_area_init(  3, 31, 52,  5, WHITE, BLACK,  TRUE);
    graphic_engine->feedback = screen_area_init( 56, 31, 21,  5, WHITE, BLACK,  TRUE);
    graphic_engine->chat     = screen_area_init(  3, 37, 74,  4, WHITE, BLACK,  TRUE);

    screen_color_box(61, 17, 9, 5, YELLOW, BLACK);

    return graphic_engine;
}

/*This function is used to free all the memory used by the graphic engine*/
void graphic_engine_destroy(Graphic_engine *ge) {

    if (!ge) return;

    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);
    screen_area_destroy(ge->chat);

    screen_destroy();
    free(ge);
}

/*This function is the one responsible of painting the game*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
    Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
    Space *space_act = NULL, *space_back = NULL, *space_next = NULL;
    Player *player = NULL;
    char obj[10];
    char *auxiliarString = NULL;
    wchar_t unicode_str[COLUMNS];
    char **chat;
    char **graphic_description_act, **graphic_description_back, **graphic_description_next;
    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[];
    int i;

    player = (Player *) game_find(game, PLAYER_BASE_ID + game_get_players_number(game));
    if (player == NULL) return;

    /* Paint the in the map area */
    screen_area_clear(ge->map);
    if ((id_act = player_get_location(player)) != NO_ID) {
        space_act = (Space *) game_find(game, id_act);

        id_back = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, NORTH)), id_act);
        id_next = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, SOUTH)), id_act);

        space_back = (Space *) game_find(game, id_back);
        space_next = (Space *) game_find(game, id_next);
        graphic_description_act = space_get_graphic_description(space_act);
        graphic_description_back = space_get_graphic_description(space_back);
        graphic_description_next = space_get_graphic_description(space_next);

        if (id_back != NO_ID) {
            if (space_is_empty(space_back) == FALSE) {
                auxiliarString = graphic_engine_get_objects_symbols(game, space_back);
                strcpy(obj, auxiliarString);
                free(auxiliarString);
            } else {
                strcpy(obj, "         ");
            }

            swprintf(unicode_str, COLUMNS, L"                  +-------------+");
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |           %2d|", (int) id_back);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_back[0]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_back[1]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_back[2]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  | %s   |", obj);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  +-------------+");
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                         ^");
            screen_area_puts(ge->map, unicode_str);
        } else {
            swprintf(unicode_str, COLUMNS, L" ");

            for (i = 0; i < 8; i++) {
                screen_area_puts(ge->map, unicode_str);
            }
        }

        if (id_act != NO_ID) {
            if (space_is_empty(space_act) == FALSE) {
                auxiliarString = graphic_engine_get_objects_symbols(game, space_act);
                strcpy(obj, auxiliarString);
                free(auxiliarString);
            } else {
                strcpy(obj, "         ");
            }


            swprintf(unicode_str, COLUMNS, L"                  +-------------+");
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  | %7s   %2d|", player_get_graphic_description((Player *) game_find(game, PLAYER_BASE_ID + 1)), (int) id_act);
            screen_area_puts(ge->map, unicode_str);
            if (space_get_direction(space_act, WEST) != NO_ID) {
                if (space_get_direction(space_act, EAST) != NO_ID) {
					swprintf(unicode_str, COLUMNS, L"        %8s  |   %s   |  %-8s", link_get_name((Link*) game_find(game, space_get_direction(space_act, WEST))), graphic_description_act[0], link_get_name((Link*) game_find(game, space_get_direction(space_act, EAST))));
            		screen_area_puts(ge->map, unicode_str);

                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                            swprintf(unicode_str, COLUMNS, L"        %4ld <--- |   %s   | ---> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        } else {
                            swprintf(unicode_str, COLUMNS, L"        %4ld <--- |   %s   | -|-> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        }
                    } else {
                        if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                            swprintf(unicode_str, COLUMNS, L"        %4ld <-|- |   %s   | ---> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        } else {
                            swprintf(unicode_str, COLUMNS, L"        %4ld <-|- |   %s   | -|-> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        }
                    }
                } else {
					swprintf(unicode_str, COLUMNS, L"        %8s  |   %s   |", link_get_name((Link*) game_find(game, space_get_direction(space_act, WEST))), graphic_description_act[0]);
            		screen_area_puts(ge->map, unicode_str);
                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        swprintf(unicode_str, COLUMNS, L"        %4ld <--- |   %s   |", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1]);
                    } else {
                        swprintf(unicode_str, COLUMNS, L"        %4ld <-|- |   %s   |", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1]);
                    }
                }
            } else {
                if (space_get_direction(space_act, EAST) != NO_ID) {
					swprintf(unicode_str, COLUMNS, L"                  |   %s   |  %-8s", graphic_description_act[0], link_get_name((Link*) game_find(game, space_get_direction(space_act, EAST))));
            		screen_area_puts(ge->map, unicode_str);
                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        swprintf(unicode_str, COLUMNS, L"                  |   %s   | ---> %ld", graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                    } else {
                        swprintf(unicode_str, COLUMNS, L"                  |   %s   | -|-> %ld", graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                    }
                } else {
					swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_act[0]);
            		screen_area_puts(ge->map, unicode_str);
                    swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_act[1]);
                }
            }
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_act[2]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  | %s   |", obj);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  +-------------+   🐦   🐤    🐥   🇪🇸");
            screen_area_puts(ge->map, unicode_str);
        }

        if (id_next != NO_ID) {
            if (space_is_empty(space_next) == FALSE) {
                auxiliarString = graphic_engine_get_objects_symbols(game, space_next);
                strcpy(obj, auxiliarString);
                free(auxiliarString);
            } else {
                strcpy(obj, "         ");
            }


            swprintf(unicode_str, COLUMNS, L"                         v");
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  +-------------+");
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |           %2d|", (int) id_next);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_next[0]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_next[1]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  |   %s   |", graphic_description_next[2]);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  | %s   |", obj);
            screen_area_puts(ge->map, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                  +-------------+");
            screen_area_puts(ge->map, unicode_str);
        }
    }

    /* Paint the in the description area */
    screen_area_clear(ge->descript);
    swprintf(unicode_str, COLUMNS, L" Objects locations:");
    screen_area_puts(ge->descript, unicode_str);

    for (i = OBJECT_BASE_ID; i < OBJECT_BASE_ID + MAX_OBJECTS; i++) {
        if ((obj_loc = object_get_location((Object *) game_find(game, i))) != NO_ID && (obj_loc < PLAYER_BASE_ID)) {
            swprintf(unicode_str, COLUMNS, L"    %6s (%d) -> %d", object_get_name((Object *) game_find(game, i)), i-OBJECT_BASE_ID, (int) obj_loc);
            screen_area_puts(ge->descript, unicode_str);
        }
    }

    obj[0] = 0;
    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(ge->descript, unicode_str);
    if (player_is_empty(player) == FALSE) {
        swprintf(unicode_str, COLUMNS, L" Inventory:");
        screen_area_puts(ge->descript, unicode_str);

        for (i = 0; i < player_get_objects_number(player); i++) {
            swprintf(unicode_str, COLUMNS, L"    %6s (%ld)", object_get_name((Object *) game_find(game, player_get_object(player, i))), player_get_object(player, i) - OBJECT_BASE_ID);
            screen_area_puts(ge->descript, unicode_str);
        }
    } else {
        swprintf(unicode_str, COLUMNS, L" The inventory is empty ");
        screen_area_puts(ge->descript, unicode_str);
    }

    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(ge->descript, unicode_str);



    for (i = 0; i < game_get_dies_number(game); i++) {
        swprintf(unicode_str, COLUMNS, L" Last Die Value: %d ", die_get_value((Die *) game_find(game, DIE_BASE_ID+game_get_dies_number(game) - i)));
        screen_area_puts(ge->descript, unicode_str);
    }
    /*We print the last die in a beautiful and visually friendly way*/
    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(ge->descript, unicode_str);

    swprintf(unicode_str, COLUMNS, L"        +-------+");
    screen_area_puts(ge->descript, unicode_str);

    switch (die_get_value((Die *) game_find(game, DIE_BASE_ID + game_get_dies_number(game)))) {
        case 1:
            swprintf(unicode_str, COLUMNS, L"        |       |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |   o   |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |       |");
            screen_area_puts(ge->descript, unicode_str);
            break;

        case 2:
            swprintf(unicode_str, COLUMNS, L"        | o     |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |       |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |     o |");
            screen_area_puts(ge->descript, unicode_str);
            break;

        case 3:
            swprintf(unicode_str, COLUMNS, L"        | o     |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |   o   |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |     o |");
            screen_area_puts(ge->descript, unicode_str);
            break;

        case 4:
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |       |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            break;

        case 5:
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        |   o   |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            break;

        case 6:
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            swprintf(unicode_str, COLUMNS, L"        | o   o |");
            screen_area_puts(ge->descript, unicode_str);
            break;
    }

    swprintf(unicode_str, COLUMNS, L"        +-------+");
    screen_area_puts(ge->descript, unicode_str);


    /* Paint the in the banner area */
    screen_area_clear(ge->banner);
    swprintf(unicode_str, COLUMNS, L"     _____                        ______                         _____ __ __");
    screen_area_puts(ge->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    / ___/ __  ______  ___  _____/ ____/___  ____  ________     / ___// // /");
    screen_area_puts(ge->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    \\__  \\/ / / / __ \\/ _ \\/ ___/ / __/ __ \\/ __ \\/  ___/_ \\   / __ \\/ // /_");
    screen_area_puts(ge->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    ___/ / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ (__  )  __/  / /_/ /__  __/");
    screen_area_puts(ge->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   /____/\\____/ ____/\\___/_/   \\____/\\____/\\____/____/\\__/____\\____/  /_/");
    screen_area_puts(ge->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"             /_/                                         /___/");
    screen_area_puts(ge->banner, unicode_str);


    /* Paint the in the help area */
    screen_area_clear(ge->help);
    swprintf(unicode_str, COLUMNS, L"                           +-+-+-+-+      G - Grasp");
    screen_area_puts(ge->help, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           |   N   |      D - Drop");
    screen_area_puts(ge->help, unicode_str);
    swprintf(unicode_str, COLUMNS, L"     Movement-> M - Move + + W + E +      T - Roll");
    screen_area_puts(ge->help, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           |   S   |      C - Check");
    screen_area_puts(ge->help, unicode_str);
    swprintf(unicode_str, COLUMNS, L"                           +-+-+-+-+      E - Exit");
    screen_area_puts(ge->help, unicode_str);

    /* Paint the in the feedback area */
    last_cmd = game_get_last_command(game);
    if (game_get_status_last_command(game) == OK) {
        swprintf(unicode_str, COLUMNS, L" %s -> OK", cmd_to_str[last_cmd-NO_CMD]);
    } else {
        swprintf(unicode_str, COLUMNS, L" %s -> ERROR", cmd_to_str[last_cmd-NO_CMD]);
    }
    screen_area_puts(ge->feedback, unicode_str);

    /* Paint the in the chat area */
    screen_area_clear(ge->chat);
    chat = game_get_last_text_description(game);
    swprintf(unicode_str, COLUMNS, L" %s", space_get_name(space_act));
	screen_area_puts(ge->chat, unicode_str);
    switch (game_get_last_command(game)) {
        case CHECK:
            switch (game_get_status_last_command(game)) {
                case ERROR:
                    swprintf(unicode_str, COLUMNS, L" There was a problem with the check.");
                    screen_area_puts(ge->chat, unicode_str);
                    break;
                case DARK:
                    swprintf(unicode_str, COLUMNS, L" It's too dark to see more details.");
                    screen_area_puts(ge->chat, unicode_str);
                    break;
                case FAR:
                    swprintf(unicode_str, COLUMNS, L" The object is not in your inventory or space.");
                    screen_area_puts(ge->chat, unicode_str);
                    break;
                default:                     
                    for (i = 0; i < MAX_TDESC_R; i++) {
                        swprintf(unicode_str, COLUMNS, L"%s", chat[i]);
                        screen_area_puts(ge->chat, unicode_str);
                    }
            }
            break;
        case GRASP:
            switch (game_get_status_last_command(game)) {
                case UNMOVABLE:
                    swprintf(unicode_str, COLUMNS, L" This object will not move any time soon.");
                    screen_area_puts(ge->chat, unicode_str);
                    break;
                default:
                    for (i = 0; i < MAX_TDESC_R; i++) {
                        swprintf(unicode_str, COLUMNS, L"%s", chat[i]);
                        screen_area_puts(ge->chat, unicode_str);
                    }
            }
            break;
        default:
            for (i = 0; i < MAX_TDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%s", chat[i]);
                screen_area_puts(ge->chat, unicode_str);
            }
    }

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

/*This function is used to get the object symbols that are printed on the spaces*/
char *graphic_engine_get_objects_symbols(Game *game, Space *space) {
    char *objects_symbols = NULL, auxiliar_name[WORD_SIZE + 1];
    int objects_number, position, i;

    if (space == NULL) return "         ";

    objects_symbols = (char *) malloc(sizeof (char)*10);
    if (objects_symbols == NULL) return "         ";

    objects_number = space_get_objects_number(space);
    position = 0;

    for (i = 0; i < objects_number; i++) {
        strcpy(auxiliar_name, object_get_name((Object *) game_find(game, space_get_object_id(space, i))));

        objects_symbols[position] = auxiliar_name[0];
        position++;

        if (i < objects_number - 1) {
            objects_symbols[position] = '|';
            position++;
        }
    }

    while (position < 9) {
        objects_symbols[position] = ' ';
        position++;
    }

    objects_symbols[position] = '\0';

    return objects_symbols;
}
