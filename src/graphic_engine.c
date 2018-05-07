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
#include "../include/game.h"
#include "../include/graphic_engine.h"
#include "../include/graphic_descriptions.h"
#include "../include/dialogue.h"

/*Graphic Engine structure, which includes the six areas that are used when playing.*/
struct _Graphic_engine {
    Area *map_left, *map_left_separator, *map_center, *map_right_separator, *map_right, *links_names, *objects_in_room_1, *objects_in_room_2, *objects_in_room_3, *inventory_1, *inventory_2, *inventory_3, *banner, *feedback, *chat;
};

/*This function is used to allocate the memory the graphic engine is going to use.*/
Graphic_engine *graphic_engine_create() {
    Graphic_engine *graphic_engine = NULL;

    screen_init(BLACK);
    graphic_engine = (Graphic_engine *) malloc(sizeof(Graphic_engine));

    graphic_engine->banner              = screen_area_init( 25,  0, 78,  6, GREEN, BLACK, FALSE);
    graphic_engine->map_left            = screen_area_init(  9,  7, 20, 42, WHITE, BLACK, FALSE);
    graphic_engine->map_left_separator  = screen_area_init( 29,  7,  6, 42, WHITE, BLACK, FALSE);
    graphic_engine->map_center          = screen_area_init( 35,  7, 20, 42, WHITE, BLACK, FALSE);
    graphic_engine->map_right_separator = screen_area_init( 55,  7,  6, 42, WHITE, BLACK, FALSE);
    graphic_engine->map_right           = screen_area_init( 61,  7, 20, 42, WHITE, BLACK, FALSE);
    graphic_engine->links_names         = screen_area_init( 88,  7, 37,  4, WHITE, BLACK,  TRUE);
    graphic_engine->objects_in_room_1   = screen_area_init( 88, 12, 37,  1, WHITE, BLACK, FALSE);
    graphic_engine->objects_in_room_2   = screen_area_init( 90, 14, 16,  5, WHITE, BLACK, FALSE);
    graphic_engine->objects_in_room_3   = screen_area_init(107, 14, 16,  5, WHITE, BLACK, FALSE);
    graphic_engine->inventory_1         = screen_area_init( 88, 21, 37,  1, WHITE, BLACK, FALSE);
    graphic_engine->inventory_2         = screen_area_init( 90, 23, 16,  5, WHITE, BLACK, FALSE);
    graphic_engine->inventory_3         = screen_area_init(107, 23, 16,  5, WHITE, BLACK, FALSE);    
    graphic_engine->feedback            = screen_area_init( 88, 45, 37, 13, WHITE, BLACK,  TRUE);
    graphic_engine->chat                = screen_area_init(  3, 50, 84,  8, WHITE, BLACK,  TRUE);

    screen_add_border( 2,  6, 86, 44, WHITE, BLACK);
    screen_add_border(87, 11, 39, 10, WHITE, BLACK);
    screen_add_border(87, 20, 39, 10, WHITE, BLACK);

    return graphic_engine;
}

/*This function is used to free all the memory used by the graphic engine*/
void graphic_engine_destroy(Graphic_engine *graphic_engine) {

    if (!graphic_engine) return;

    screen_area_destroy(graphic_engine->banner);
    screen_area_destroy(graphic_engine->map_left);
    screen_area_destroy(graphic_engine->map_left_separator);
    screen_area_destroy(graphic_engine->map_center);
    screen_area_destroy(graphic_engine->map_right_separator);
    screen_area_destroy(graphic_engine->map_right);
    screen_area_destroy(graphic_engine->links_names);
    screen_area_destroy(graphic_engine->objects_in_room_1);
    screen_area_destroy(graphic_engine->objects_in_room_2);
    screen_area_destroy(graphic_engine->objects_in_room_3);
    screen_area_destroy(graphic_engine->inventory_1);
    screen_area_destroy(graphic_engine->inventory_2);
    screen_area_destroy(graphic_engine->inventory_3);    
    screen_area_destroy(graphic_engine->feedback);
    screen_area_destroy(graphic_engine->chat);

    screen_destroy();
    free(graphic_engine);
}

/*This function is the one responsible of painting the game*/
void graphic_engine_paint_game(Graphic_engine *graphic_engine, Game *game) {
    Id id_act = NO_ID, id_north = NO_ID, id_west = NO_ID, id_south = NO_ID, id_east = NO_ID;
    Space *space_act = NULL, *space_north = NULL, *space_west = NULL, *space_south = NULL, *space_east = NULL;
    Link *link_north = NULL, *link_west = NULL, *link_south = NULL, *link_east = NULL;
    Player *player = NULL;
    wchar_t unicode_str[COLUMNS];
    wchar_t **graphic_description_act, **graphic_description_north, **graphic_description_west, **graphic_description_south, **graphic_description_east, graphic_description_not_illuminated[MAX_GDESC_R][MAX_GDESC_C];
    wchar_t dialogue[MAX_DIA_R][MAX_DIA_C];
    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[];
    int i;
    long int j;
    BOOL space_glowing = FALSE;

    player = (Player *) game_find(game, PLAYER_BASE_ID + game_get_players_number(game));
    if (player == NULL) return;

    id_act = player_get_location(player);
    space_act = (Space *) game_find(game, id_act);

    wcscpy(graphic_description_not_illuminated[0], NOT_ILLUMINATED_0);
    wcscpy(graphic_description_not_illuminated[1], NOT_ILLUMINATED_1);
    wcscpy(graphic_description_not_illuminated[2], NOT_ILLUMINATED_2);
    wcscpy(graphic_description_not_illuminated[3], NOT_ILLUMINATED_3);
    wcscpy(graphic_description_not_illuminated[4], NOT_ILLUMINATED_4);
    wcscpy(graphic_description_not_illuminated[5], NOT_ILLUMINATED_5);
    wcscpy(graphic_description_not_illuminated[6], NOT_ILLUMINATED_6);
    wcscpy(graphic_description_not_illuminated[7], NOT_ILLUMINATED_7);
    wcscpy(graphic_description_not_illuminated[8], NOT_ILLUMINATED_8);
    wcscpy(graphic_description_not_illuminated[9], NOT_ILLUMINATED_9);

    /* Paint the in the map_center area */
    screen_area_clear(graphic_engine->map_center);
    if (id_act != NO_ID) {        
        id_north = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, NORTH)), id_act);
        id_south = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, SOUTH)), id_act);

        if (id_north != NO_ID) {
            space_north = (Space *) game_find(game, id_north);
            space_glowing = FALSE;
    		for (j = 0; j < space_get_objects_number((Space *) game_find(game, id_north)); j++) {
    			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_north), j)), GLOWING)) {
    				space_glowing = TRUE;
    				break;
    			}
    		}
            if (space_check_tag(space_north, ILLUMINATED) == TRUE || space_glowing == TRUE) {                
                graphic_description_north = space_get_graphic_description(space_north);
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"%-17S %2d", space_get_name(space_north), space_get_objects_number(space_north));
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_north[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                }
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                if (link_get_status((Link*) game_find(game, space_get_direction(space_act, NORTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
                else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
            } else {
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"Darkness            ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_not_illuminated[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                }
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                if (link_get_status((Link*) game_find(game, space_get_direction(space_act, NORTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
                else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
            }
        } else {
            swprintf(unicode_str, COLUMNS, L"                    ");
            for (i = 0; i < 15; i++) {
                screen_area_puts(graphic_engine->map_center, unicode_str);
            }
        }

        if (id_act != NO_ID) { 
        	space_glowing = FALSE;
	    	for (j = 0; j < player_get_objects_number((Player *) game_find(game, PLAYER_BASE_ID+1)); j++) {
	    		if (object_check_tag((Object *) game_find(game, player_get_object_id((Player *) game_find(game, PLAYER_BASE_ID+1), j)), GLOWING)) {
	    			space_glowing = TRUE;
	    			break;
	    		}
	    	}
	    	if (!space_glowing) {
	    		for (j = 0; j < space_get_objects_number((Space *) game_find(game, id_act)); j++) {
	    			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_act), j)), GLOWING)) {
	    				space_glowing = TRUE;
	    				break;
	    			}
	    		}
	    	}
            if (space_check_tag(space_act, ILLUMINATED) == TRUE || space_glowing == TRUE) {           
                graphic_description_act = space_get_graphic_description(space_act);
                swprintf(unicode_str, COLUMNS, L"%-17S %2d", space_get_name(space_act), space_get_objects_number(space_act));
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_act[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                } 
            } else {
                swprintf(unicode_str, COLUMNS, L"Darkness            ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_not_illuminated[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                }
            }
        } else {
            swprintf(unicode_str, COLUMNS, L" ");
            for (i = 0; i < 11; i++) {
                screen_area_puts(graphic_engine->map_center, unicode_str);
            }
        }

        if (id_south != NO_ID) {
            space_south = (Space *) game_find(game, id_south);
            space_glowing = FALSE;
    		for (j = 0; j < space_get_objects_number((Space *) game_find(game, id_south)); j++) {
    			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_south), j)), GLOWING)) {
    				space_glowing = TRUE;
    				break;
    			}
    		}   
            if (space_check_tag(space_south, ILLUMINATED) == TRUE || space_glowing == TRUE) {  
                graphic_description_south = space_get_graphic_description(space_south);
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);            
                if (link_get_status((Link*) game_find(game, space_get_direction(space_act, SOUTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
                else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");            
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"%-17S %2d", space_get_name(space_south), space_get_objects_number(space_south));
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_south[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                }
            } else {
                swprintf(unicode_str, COLUMNS, L"                    ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                if (link_get_status((Link*) game_find(game, space_get_direction(space_act, SOUTH))) == OPEN) swprintf(unicode_str, COLUMNS, L"        ↑  ↓        ");
                else swprintf(unicode_str, COLUMNS, L"        ⤉  ⤈        ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                swprintf(unicode_str, COLUMNS, L"Darkness            ");
                screen_area_puts(graphic_engine->map_center, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_not_illuminated[i]);
                    screen_area_puts(graphic_engine->map_center, unicode_str);
                }             
            }
        }
    }

    /* Paint the in the map_left area */
    screen_area_clear(graphic_engine->map_left);
    if (id_act != NO_ID) {
        id_west = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, WEST)), id_act);
        if (id_west != NO_ID) {
            space_west = (Space *) game_find(game, id_west);
            space_glowing = FALSE;
    		for (j = 0; j < space_get_objects_number((Space *) game_find(game, id_west)); j++) {
    			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_west), j)), GLOWING)) {
    				space_glowing = TRUE;
    				break;
    			}
    		} 
            if (space_check_tag(space_west, ILLUMINATED) == TRUE || space_glowing == TRUE) { 
                graphic_description_west = space_get_graphic_description(space_west);

                swprintf(unicode_str, COLUMNS, L"                    ");
                for (i = 0; i < 15; i++) {
                    screen_area_puts(graphic_engine->map_left, unicode_str);
                }
                swprintf(unicode_str, COLUMNS, L"%-17S %2d", space_get_name(space_west), space_get_objects_number(space_west));
                screen_area_puts(graphic_engine->map_left, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_west[i]);
                    screen_area_puts(graphic_engine->map_left, unicode_str);
                }
            } else {
                swprintf(unicode_str, COLUMNS, L"Darkness            ");
                for (i = 0; i < 16; i++) {
                    screen_area_puts(graphic_engine->map_left, unicode_str);
                }
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_not_illuminated[i]);
                    screen_area_puts(graphic_engine->map_left, unicode_str);
                }            
            }
        }        
    }

    /* Paint the in the map_left_separator area */
    screen_area_clear(graphic_engine->map_left_separator);
    if (id_act != NO_ID) {
        if (id_west != NO_ID) {
            swprintf(unicode_str, COLUMNS, L"   ");
            for (i = 0; i < 20; i++) {
                screen_area_puts(graphic_engine->map_left_separator, unicode_str);
            }
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, WEST))) == OPEN) {
                swprintf(unicode_str, COLUMNS, L"  →  ");
                screen_area_puts(graphic_engine->map_left_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ←  ");
                screen_area_puts(graphic_engine->map_left_separator, unicode_str);
            } else {
                swprintf(unicode_str, COLUMNS, L"  ⇸  ");
                screen_area_puts(graphic_engine->map_left_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ⇷  ");
                screen_area_puts(graphic_engine->map_left_separator, unicode_str);
            }            
        }
    }

    /* Paint the in the map_right area */
    screen_area_clear(graphic_engine->map_right);
    if (id_act != NO_ID) {
        id_east = link_get_other_side((Link*) game_find(game, space_get_direction(space_act, EAST)), id_act);
        if (id_east != NO_ID) {
            space_east = (Space *) game_find(game, id_east);
            space_glowing = FALSE;
    		for (j = 0; j < space_get_objects_number( (Space *) game_find(game, id_east)); j++) {
    			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_east), j)), GLOWING)) {
    				space_glowing = TRUE;
    				break;
    			}
    		}
            if (space_check_tag(space_east, ILLUMINATED) == TRUE || space_glowing == TRUE) { 
                graphic_description_east = space_get_graphic_description(space_east);

                swprintf(unicode_str, COLUMNS, L"                    ");
                for (i = 0; i < 15; i++) {
                    screen_area_puts(graphic_engine->map_right, unicode_str);
                }
                swprintf(unicode_str, COLUMNS, L"%-17S %2d", space_get_name(space_east), space_get_objects_number(space_east));
                screen_area_puts(graphic_engine->map_right, unicode_str);
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_east[i]);
                    screen_area_puts(graphic_engine->map_right, unicode_str);
                }
            } else {
                swprintf(unicode_str, COLUMNS, L"Darkness            ");
                for (i = 0; i < 16; i++) {
                    screen_area_puts(graphic_engine->map_right, unicode_str);
                }
                for (i = 0; i < MAX_GDESC_R; i++) {
                    swprintf(unicode_str, COLUMNS, L"%S", graphic_description_not_illuminated[i]);
                    screen_area_puts(graphic_engine->map_right, unicode_str);
                }            
            }
        }
    }

    /* Paint the in the map_right_separator area */
    screen_area_clear(graphic_engine->map_right_separator);
    if (id_act != NO_ID) {
        if (id_east != NO_ID) {
            swprintf(unicode_str, COLUMNS, L"   ");
            for (i = 0; i < 20; i++) {
                screen_area_puts(graphic_engine->map_right_separator, unicode_str);
            }
            if (link_get_status((Link*) game_find(game, space_get_direction(space_act, EAST))) == OPEN) {
                swprintf(unicode_str, COLUMNS, L"  →  ");
                screen_area_puts(graphic_engine->map_right_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ←  ");
                screen_area_puts(graphic_engine->map_right_separator, unicode_str);
            } else {
                swprintf(unicode_str, COLUMNS, L"  ⇸  ");
                screen_area_puts(graphic_engine->map_right_separator, unicode_str);
                swprintf(unicode_str, COLUMNS, L"  ⇷  ");
                screen_area_puts(graphic_engine->map_right_separator, unicode_str);
            }            
        }
    }

    /* Paint the in the links names area */
    screen_area_clear(graphic_engine->links_names);
    link_north = (Link*) game_find(game, space_get_direction(space_act, NORTH));
    link_west  = (Link*) game_find(game, space_get_direction(space_act,  WEST));
    link_south = (Link*) game_find(game, space_get_direction(space_act, SOUTH));
    link_east  = (Link*) game_find(game, space_get_direction(space_act,  EAST));
    if (link_north != NULL) swprintf(unicode_str, COLUMNS, L" Northern link: %S", link_get_name(link_north));
    else swprintf(unicode_str, COLUMNS, L" Northern link: X");
    screen_area_puts(graphic_engine->links_names, unicode_str);
    if (link_west != NULL) swprintf(unicode_str, COLUMNS, L" Western link: %S", link_get_name(link_west));
    else swprintf(unicode_str, COLUMNS, L" Western link: X");
    screen_area_puts(graphic_engine->links_names, unicode_str);    
    if (link_south != NULL) swprintf(unicode_str, COLUMNS, L" Southern link: %S", link_get_name(link_south));
    else swprintf(unicode_str, COLUMNS, L" Southern link: X");
    screen_area_puts(graphic_engine->links_names, unicode_str);
    if (link_east != NULL) swprintf(unicode_str, COLUMNS, L" Eastern link: %S", link_get_name(link_east));
    else swprintf(unicode_str, COLUMNS, L" Eastern link: X");;
    screen_area_puts(graphic_engine->links_names, unicode_str);    

    /* Paint the in the objects_in_room areas */
    screen_area_clear(graphic_engine->objects_in_room_1);
    screen_area_clear(graphic_engine->objects_in_room_2);
    screen_area_clear(graphic_engine->objects_in_room_3);
    space_glowing = FALSE;
	for (j = 0; j < player_get_objects_number( (Player *) game_find(game, PLAYER_BASE_ID+1)); j++) {
		if (object_check_tag((Object *) game_find(game, player_get_object_id((Player *) game_find(game, PLAYER_BASE_ID+1), j)), GLOWING)) {
			space_glowing = TRUE;
			break;
		}
	}
	if (!space_glowing) {
		for (j = 0; j < space_get_objects_number( (Space *) game_find(game, id_act)); j++) {
			if (object_check_tag((Object *) game_find(game, space_get_object_id((Space *) game_find(game, id_act), j)), GLOWING)) {
				space_glowing = TRUE;
				break;
			}
		}
	}    
    if (space_check_tag(space_act, ILLUMINATED) == TRUE || space_glowing == TRUE) {
        swprintf(unicode_str, COLUMNS, L" Objects in this room:");
        screen_area_puts(graphic_engine->objects_in_room_1, unicode_str);
        for (i = 0; i < space_get_objects_number(space_act); i++) {        
            swprintf(unicode_str, COLUMNS, L"-%-14S", object_get_name((Object *) game_find(game, space_get_object_id(space_act, i))));
            if (i%2 == 0) {
                screen_area_puts(graphic_engine->objects_in_room_2, unicode_str);
            } else {
                screen_area_puts(graphic_engine->objects_in_room_3, unicode_str);
            }       
        }
    } else {
        swprintf(unicode_str, COLUMNS, L" You can't see objects in the dark.");
        screen_area_puts(graphic_engine->objects_in_room_1, unicode_str);
    }

    /* Paint the in the inventory areas */
    screen_area_clear(graphic_engine->inventory_1);
    screen_area_clear(graphic_engine->inventory_2);
    screen_area_clear(graphic_engine->inventory_3);
    swprintf(unicode_str, COLUMNS, L" Inventory:");
    screen_area_puts(graphic_engine->inventory_1, unicode_str);
    for (i = 0; i < player_get_objects_number(player); i++) {        
        swprintf(unicode_str, COLUMNS, L"-%-14S", object_get_name((Object *) game_find(game, player_get_object_id(player, i))));
        if (i%2 == 0) {
            screen_area_puts(graphic_engine->inventory_2, unicode_str);
        } else {
            screen_area_puts(graphic_engine->inventory_3, unicode_str);
        } 
    }    

    /* Paint the in the banner area */
    screen_area_clear(graphic_engine->banner);
    swprintf(unicode_str, COLUMNS, L"     _____                        ______                         _____ __ __");
    screen_area_puts(graphic_engine->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    / ___/ __  ______  ___  _____/ ____/___  ____  ________     / ___// // /");
    screen_area_puts(graphic_engine->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    \\__  \\/ / / / __ \\/ _ \\/ ___/ / __/ __ \\/ __ \\/  ___/_ \\   / __ \\/ // /_");
    screen_area_puts(graphic_engine->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"    ___/ / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ (__  )  __/  / /_/ /__  __/");
    screen_area_puts(graphic_engine->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"   /____/\\____/ ____/\\___/_/   \\____/\\____/\\____/____/\\__/____\\____/  /_/");
    screen_area_puts(graphic_engine->banner, unicode_str);
    swprintf(unicode_str, COLUMNS, L"             /_/                                         /___/");
    screen_area_puts(graphic_engine->banner, unicode_str);

    /* Paint the in the feedback area */
    last_cmd = game_get_last_command(game);
    if (game_get_status_last_command(game) == OK) {
        swprintf(unicode_str, COLUMNS, L"      %10s →  OK", cmd_to_str[last_cmd-NO_CMD]);
    } else {
        swprintf(unicode_str, COLUMNS, L"      %10s →  ERROR", cmd_to_str[last_cmd-NO_CMD]);
    }
    screen_area_puts(graphic_engine->feedback, unicode_str);

    /* Paint the in the chat area */
    screen_area_clear(graphic_engine->chat);
    dialogue_generate(game, dialogue);
    for (i = 0; i < MAX_DIA_R; i++) {        
        screen_area_puts(graphic_engine->chat, dialogue[i]);
    }

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}