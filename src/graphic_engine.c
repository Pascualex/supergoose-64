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
    Area *map_left, *map_left_separator, *map_center, *map_right_separator, *map_right, *descript, *banner, *feedback, *chat;
};

/*This function is used to allocate the memory the graphic engine is going to use.*/
Graphic_engine *graphic_engine_create() {
    Graphic_engine *graphic_engine = NULL;

    screen_init(BLACK);
    graphic_engine = (Graphic_engine *) malloc(sizeof(Graphic_engine));

    graphic_engine->banner              = screen_area_init( 25,  0, 78,  6, GREEN,  BLACK, FALSE);
    graphic_engine->map_left            = screen_area_init(  9,  7, 20, 42, WHITE,  BLACK, FALSE);
    graphic_engine->map_left_separator  = screen_area_init( 29,  7,  6, 42, WHITE,  BLACK, FALSE);
    graphic_engine->map_center          = screen_area_init( 35,  7, 20, 42, WHITE,  BLACK, FALSE);
    graphic_engine->map_right_separator = screen_area_init( 55,  7,  6, 42, WHITE,  BLACK, FALSE);
    graphic_engine->map_right           = screen_area_init( 61,  7, 20, 42, WHITE,  BLACK, FALSE);
    graphic_engine->descript            = screen_area_init( 88,  7, 37, 37, WHITE,  BLACK,  TRUE);
    graphic_engine->feedback            = screen_area_init( 88, 45, 37, 13, WHITE,  BLACK,  TRUE);
    graphic_engine->chat                = screen_area_init(  3, 50, 84,  8, WHITE,  BLACK,  TRUE);

    screen_add_border( 2, 6, 86, 44, WHITE, BLACK);

    return graphic_engine;
}

/*This function is used to free all the memory used by the graphic engine*/
void graphic_engine_destroy(Graphic_engine *ge) {

    if (!ge) return;

    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->map_center);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->feedback);
    screen_area_destroy(ge->chat);

    screen_destroy();
    free(ge);
}

/*This function is the one responsible of painting the game*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
    Id id_act = NO_ID, id_north = NO_ID, id_west = NO_ID, id_south = NO_ID, id_east = NO_ID, obj_loc = NO_ID;
    Space *space_act = NULL, *space_north = NULL, *space_west = NULL, *space_south = NULL, *space_east = NULL;
    Player *player = NULL;
    wchar_t unicode_str[COLUMNS];
    wchar_t **chat;
    wchar_t **graphic_description_act, **graphic_description_north, **graphic_description_west, **graphic_description_south, **graphic_description_east;
    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[];
    int i;

    player = (Player *) game_find(game, PLAYER_BASE_ID + game_get_players_number(game));
    if (player == NULL) return;

    id_act = player_get_location(player);
    space_act = (Space *) game_find(game, id_act);    

    /* Paint the in the map_center area */
    screen_area_clear(ge->map_center);
    if (id_act != NO_ID) {        
        id_north = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, NORTH)), id_act);
        id_south = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, SOUTH)), id_act);

        if (id_north != NO_ID) {
            space_north = (Space *) game_find(game, id_north);
            graphic_description_north = space_get_graphic_description(space_north);

            swprintf(unicode_str, COLUMNS, L"                    ");
            screen_area_puts(ge->map_center, unicode_str);
            swprintf(unicode_str, COLUMNS, L"                    ");
            screen_area_puts(ge->map_center, unicode_str);
            swprintf(unicode_str, COLUMNS, L"%S", space_get_name(space_north));
            screen_area_puts(ge->map_center, unicode_str);
            for (i = 0; i < MAX_GDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", graphic_description_north[i]);
                screen_area_puts(ge->map_center, unicode_str);
            }
            swprintf(unicode_str, COLUMNS, L"                    ");
            screen_area_puts(ge->map_center, unicode_str);
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, NORTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
            else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");
            screen_area_puts(ge->map_center, unicode_str);
        } else {
            swprintf(unicode_str, COLUMNS, L"                    ");
            for (i = 0; i < 15; i++) {
                screen_area_puts(ge->map_center, unicode_str);
            }
        }

        if (id_act != NO_ID) {            
            graphic_description_act = space_get_graphic_description(space_act);

            swprintf(unicode_str, COLUMNS, L"%S", space_get_name(space_act));
            screen_area_puts(ge->map_center, unicode_str);
            for (i = 0; i < MAX_GDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", graphic_description_act[i]);
                screen_area_puts(ge->map_center, unicode_str);
            }
        } else {
            swprintf(unicode_str, COLUMNS, L" ");
            for (i = 0; i < 11; i++) {
                screen_area_puts(ge->map_center, unicode_str);
            }
        }

        if (id_south != NO_ID) {
            space_south = (Space *) game_find(game, id_south);   
            graphic_description_south = space_get_graphic_description(space_south);

            swprintf(unicode_str, COLUMNS, L"                    ");
            screen_area_puts(ge->map_center, unicode_str);            
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, SOUTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
            else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");            
            screen_area_puts(ge->map_center, unicode_str);
            swprintf(unicode_str, COLUMNS, L"%S", space_get_name(space_south));
            screen_area_puts(ge->map_center, unicode_str);
            for (i = 0; i < MAX_GDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", graphic_description_south[i]);
                screen_area_puts(ge->map_center, unicode_str);
            }
        }
    }

    /* Paint the in the map_left area */
    screen_area_clear(ge->map_left);
    if (id_act != NO_ID) {
        id_west = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act);

        if (id_west != NO_ID) {
            space_west = (Space *) game_find(game, id_west);
            graphic_description_west = space_get_graphic_description(space_west);

            swprintf(unicode_str, COLUMNS, L"                    ");
            for (i = 0; i < 15; i++) {
                screen_area_puts(ge->map_left, unicode_str);
            }
            swprintf(unicode_str, COLUMNS, L"%S", space_get_name(space_west));
            screen_area_puts(ge->map_left, unicode_str);
            for (i = 0; i < MAX_GDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", graphic_description_west[i]);
                screen_area_puts(ge->map_left, unicode_str);
            }
        }
    }

    /* Paint the in the map_left_separator area */
    screen_area_clear(ge->map_left_separator);
    if (id_act != NO_ID) {
        if (id_west != NO_ID) {
            swprintf(unicode_str, COLUMNS, L"   ");
            for (i = 0; i < 20; i++) {
                screen_area_puts(ge->map_left_separator, unicode_str);
            }
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                swprintf(unicode_str, COLUMNS, L"  → ");
                screen_area_puts(ge->map_left_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ← ");
                screen_area_puts(ge->map_left_separator, unicode_str);
            } else {
                swprintf(unicode_str, COLUMNS, L"  ⇸ ");
                screen_area_puts(ge->map_left_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ⇷ ");
                screen_area_puts(ge->map_left_separator, unicode_str);
            }            
        }
    }

    /* Paint the in the map_right area */
    screen_area_clear(ge->map_right);
    if (id_act != NO_ID) {
        id_east = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act);

        if (id_east != NO_ID) {
            space_east = (Space *) game_find(game, id_east);
            graphic_description_east = space_get_graphic_description(space_east);

            swprintf(unicode_str, COLUMNS, L"                    ");
            for (i = 0; i < 15; i++) {
                screen_area_puts(ge->map_right, unicode_str);
            }
            swprintf(unicode_str, COLUMNS, L"%S", space_get_name(space_east));
            screen_area_puts(ge->map_right, unicode_str);
            for (i = 0; i < MAX_GDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", graphic_description_east[i]);
                screen_area_puts(ge->map_right, unicode_str);
            }
        }
    }

    /* Paint the in the map_right_separator area */
    screen_area_clear(ge->map_right_separator);
    if (id_act != NO_ID) {
        if (id_east != NO_ID) {
            swprintf(unicode_str, COLUMNS, L"   ");
            for (i = 0; i < 20; i++) {
                screen_area_puts(ge->map_right_separator, unicode_str);
            }
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                swprintf(unicode_str, COLUMNS, L"  → ");
                screen_area_puts(ge->map_right_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ← ");
                screen_area_puts(ge->map_right_separator, unicode_str);
            } else {
                swprintf(unicode_str, COLUMNS, L"  ⇸ ");
                screen_area_puts(ge->map_right_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ⇷ ");
                screen_area_puts(ge->map_right_separator, unicode_str);
            }            
        }
    }

    /* Paint the in the description area */
    screen_area_clear(ge->descript);
    swprintf(unicode_str, COLUMNS, L" Objects locations:");
    screen_area_puts(ge->descript, unicode_str);

    for (i = OBJECT_BASE_ID; i < OBJECT_BASE_ID + MAX_OBJECTS; i++) {
        if ((obj_loc = object_get_location((Object *) game_find(game, i))) != NO_ID && (obj_loc < PLAYER_BASE_ID)) {
            swprintf(unicode_str, COLUMNS, L"  %9S (%ld) -> %d", object_get_name((Object *) game_find(game, i)), i-OBJECT_BASE_ID, (int) obj_loc);
            screen_area_puts(ge->descript, unicode_str);
        }
    }

    swprintf(unicode_str, COLUMNS, L" ");
    screen_area_puts(ge->descript, unicode_str);
    if (player_is_empty(player) == FALSE) {
        swprintf(unicode_str, COLUMNS, L" Inventory:");
        screen_area_puts(ge->descript, unicode_str);

        for (i = 0; i < player_get_objects_number(player); i++) {
            swprintf(unicode_str, COLUMNS, L"  %9S (%ld)", object_get_name((Object *) game_find(game, player_get_object(player, i))), player_get_object(player, i) - OBJECT_BASE_ID);
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
    swprintf(unicode_str, COLUMNS, L" %S", space_get_name(space_act));
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
                        swprintf(unicode_str, COLUMNS, L"%S", chat[i]);
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
                        swprintf(unicode_str, COLUMNS, L"%S", chat[i]);
                        screen_area_puts(ge->chat, unicode_str);
                    }
            }
            break;
        default:
            for (i = 0; i < MAX_TDESC_R; i++) {
                swprintf(unicode_str, COLUMNS, L"%S", chat[i]);
                screen_area_puts(ge->chat, unicode_str);
            }
    }

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

/*This function is used to get the object symbols that are printed on the spaces*/
wchar_t *graphic_engine_get_objects_symbols(Game *game, Space *space) {
    wchar_t *objects_symbols = NULL, auxiliar_name[WORD_SIZE + 1];
    int objects_number, position, i;

    if (space == NULL) return L"         ";

    objects_symbols = (wchar_t *) malloc(sizeof(wchar_t)*10);
    if (objects_symbols == NULL) return L"         ";

    objects_number = space_get_objects_number(space);
    position = 0;

    for (i = 0; i < objects_number; i++) {
        wcscpy(auxiliar_name, object_get_name((Object *) game_find(game, space_get_object_id(space, i))));

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
