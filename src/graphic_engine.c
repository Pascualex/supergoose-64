/** 
 * @brief It defines the graphic engine functions
 * @file graphic_engine.c
 * @author
 * @version 1.0 
 * @date 06-04-2018
 * @updated 07-04-2018
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdlib.h>
#include <stdio.h>
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
    static Graphic_engine *ge = NULL;

    if (ge) return ge;

    screen_init(BLACK);
    ge = (Graphic_engine *) malloc(sizeof (Graphic_engine));

    ge->banner =   screen_area_init(  2,  0, 79,  6, GREEN, BLACK, FALSE);
    ge->map =      screen_area_init(  3,  7, 49, 23, BLUE,  BLACK,  TRUE);
    ge->descript = screen_area_init( 53,  7, 24, 23, WHITE, BLACK,  TRUE);
    ge->help =     screen_area_init(  3, 31, 52,  5, WHITE, BLACK,  TRUE);
    ge->feedback = screen_area_init( 56, 31, 21,  5, WHITE, BLACK,  TRUE);
    ge->chat =     screen_area_init(  3, 37, 74,  3, WHITE, BLACK,  TRUE);

    screen_color_box(61, 17, 9, 5, YELLOW, BLACK);

    return ge;
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
    char str[255];
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

            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |           %2d|", (int) id_back);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_back[0]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_back[1]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_back[2]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  | %s   |", obj);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "                         ^");
            screen_area_puts(ge->map, str);
        } else {
            sprintf(str, " ");

            for (i = 0; i < 8; i++) {
                screen_area_puts(ge->map, str);
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


            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "                  | %7s   %2d|", player_get_graphic_description((Player *) game_find(game, PLAYER_BASE_ID + 1)), (int) id_act);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_act[0]);
            screen_area_puts(ge->map, str);
            if (space_get_direction(space_act, WEST) != NO_ID) {
                if (space_get_direction(space_act, EAST) != NO_ID) {
                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                            sprintf(str, "        %4ld <--- |   %s   | ---> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        } else {
                            sprintf(str, "        %4ld <--- |   %s   | -|-> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        }
                    } else {
                        if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                            sprintf(str, "        %4ld <-|- |   %s   | ---> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        } else {
                            sprintf(str, "        %4ld <-|- |   %s   | -|-> %ld", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                        }
                    }
                } else {
                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        sprintf(str, "        %4ld <--- |   %s   |", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1]);
                    } else {
                        sprintf(str, "        %4ld <-|- |   %s   |", link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act), graphic_description_act[1]);
                    }
                }
            } else {
                if (space_get_direction(space_act, EAST) != NO_ID) {
                    if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                        sprintf(str, "                  |   %s   | ---> %ld", graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                    } else {
                        sprintf(str, "                  |   %s   | -|-> %ld", graphic_description_act[1], link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act));
                    }
                } else {
                    sprintf(str, "                  |   %s   |", graphic_description_act[1]);
                }
            }
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_act[2]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  | %s   |", obj);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
        }

        if (id_next != NO_ID) {
            if (space_is_empty(space_next) == FALSE) {
                auxiliarString = graphic_engine_get_objects_symbols(game, space_next);
                strcpy(obj, auxiliarString);
                free(auxiliarString);
            } else {
                strcpy(obj, "         ");
            }


            sprintf(str, "                         v");
            screen_area_puts(ge->map, str);
            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |           %2d|", (int) id_next);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_next[0]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_next[1]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  |   %s   |", graphic_description_next[2]);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  | %s   |", obj);
            screen_area_puts(ge->map, str);
            sprintf(str, "                  +-------------+");
            screen_area_puts(ge->map, str);
        }
    }

    /* Paint the in the description area */
    screen_area_clear(ge->descript);
    sprintf(str, " Objects locations:");
    screen_area_puts(ge->descript, str);

    for (i = OBJECT_BASE_ID; i < OBJECT_BASE_ID + MAX_OBJECTS; i++) {
        if ((obj_loc = object_get_location((Object *) game_find(game, i))) != NO_ID && (obj_loc < PLAYER_BASE_ID)) {
            sprintf(str, "    %6s (%d) -> %d", object_get_name((Object *) game_find(game, i)), i - OBJECT_BASE_ID, (int) obj_loc);
            screen_area_puts(ge->descript, str);
        }
    }

    obj[0] = 0;
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);
    if (player_is_empty(player) == FALSE) {
        sprintf(str, " Inventory:");
        screen_area_puts(ge->descript, str);

        for (i = 0; i < player_get_objects_number(player); i++) {
            sprintf(str, "    %6s (%ld)", object_get_name((Object *) game_find(game, player_get_object(player, i))), player_get_object(player, i) - OBJECT_BASE_ID);
            screen_area_puts(ge->descript, str);
        }
    } else {
        sprintf(str, " The inventory is empty ");
        screen_area_puts(ge->descript, str);
    }

    sprintf(str, " ");
    screen_area_puts(ge->descript, str);



    for (i = 0; i < game_get_dies_number(game); i++) {
        sprintf(str, " Last Die Value: %d ", die_get_value((Die *) game_find(game, DIE_BASE_ID + game_get_dies_number(game) - i)));
        screen_area_puts(ge->descript, str);
    }
    /*We print the last die in a beautiful and visually friendly way*/
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);

    sprintf(str, "        +-------+");
    screen_area_puts(ge->descript, str);

    switch (die_get_value((Die *) game_find(game, DIE_BASE_ID + game_get_dies_number(game)))) {
        case 1:
            sprintf(str, "        |       |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |   o   |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |       |");
            screen_area_puts(ge->descript, str);
            break;

        case 2:
            sprintf(str, "        | o     |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |       |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |     o |");
            screen_area_puts(ge->descript, str);
            break;

        case 3:
            sprintf(str, "        | o     |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |   o   |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |     o |");
            screen_area_puts(ge->descript, str);
            break;

        case 4:
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |       |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            break;

        case 5:
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        |   o   |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            break;

        case 6:
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            sprintf(str, "        | o   o |");
            screen_area_puts(ge->descript, str);
            break;
    }

    sprintf(str, "        +-------+");
    screen_area_puts(ge->descript, str);


    /* Paint the in the banner area */
    sprintf(str, "    _____                        ______                         _____ __ __");
    screen_area_puts(ge->banner, str);
    sprintf(str, "   / ___/ __  ______  ___  _____/ ____/___  ____  ________     / ___// // /");
    screen_area_puts(ge->banner, str);
    sprintf(str, "   \\__  \\/ / / / __ \\/ _ \\/ ___/ / __/ __ \\/ __ \\/  ___/_ \\   / __ \\/ // /_");
    screen_area_puts(ge->banner, str);
    sprintf(str, "   ___/ / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ (__  )  __/  / /_/ /__  __/");
    screen_area_puts(ge->banner, str);
    sprintf(str, "  /____/\\____/ ____/\\___/_/   \\____/\\____/\\____/____/\\__/____\\____/  /_/");
    screen_area_puts(ge->banner, str);
    sprintf(str, "            /_/                                         /___/");
    screen_area_puts(ge->banner, str);


    /* Paint the in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " ");
    screen_area_puts(ge->help, str);
    sprintf(str, "                           +-+-+-+-+      G - Grasp");
    screen_area_puts(ge->help, str);
    sprintf(str, "                           |   N   |      D - Drop");
    screen_area_puts(ge->help, str);
    sprintf(str, "     Movement-> M - Move + + W + E +      T - Roll");
    screen_area_puts(ge->help, str);
    sprintf(str, "                           |   S   |      C - Check");
    screen_area_puts(ge->help, str);
    sprintf(str, "                           +-+-+-+-+      E - Exit");
    screen_area_puts(ge->help, str);

    /* Paint the in the feedback area */
    last_cmd = game_get_last_command(game);
    if (game_get_status_last_command(game) == OK) {
        sprintf(str, " %s -> OK", cmd_to_str[last_cmd - NO_CMD]);
    } else {
        sprintf(str, " %s -> ERROR", cmd_to_str[last_cmd - NO_CMD]);
    }
    screen_area_puts(ge->feedback, str);

    /* Paint the in the chat area */
    screen_area_clear(ge->chat);
    chat = game_get_last_text_description(game);
    for (i = 0; i < MAX_TDESC_R; i++) {
        strcpy(str, chat[i]);
        screen_area_puts(ge->chat, str);
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
