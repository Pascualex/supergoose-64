#undef __STRICT_ANSI__

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <iconv.h>
/*Own libraries*/
#include "../include/game.h"
#include "../include/game_management.h"
#include "../include/graphic_descriptions.h"
#include "nfd.h"

void select_space_graphic_description(wchar_t graphic_description[MAX_GDESC_R][MAX_GDESC_C], wchar_t graphic_description_type[WORD_SIZE]);

/*This function is used to load the spaces from the given file. It works side by side with game create from file.*/
STATUS game_management_load_spaces(Game *game, char *filename) {
    FILE *file = NULL;
    wchar_t line_unicode[WORD_SIZE];
    wchar_t name[WORD_SIZE];
    wchar_t graphic_description_type[WORD_SIZE];
    wchar_t graphic_description[MAX_GDESC_R][MAX_GDESC_C];
    wchar_t basic_description[MAX_TDESC_R][MAX_TDESC_C];
    wchar_t check_description[MAX_TDESC_R][MAX_TDESC_C];
    wchar_t *toks = NULL;
    wchar_t *buffer;
    TAG tags[MAX_TAGS];
    Id id, directions_ids[6];
    Space *space = NULL;
    DIRECTION direction;
    int i,j;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;
 
    while (fgetws(line_unicode, WORD_SIZE, file)) {
        if (wcsncmp(L"#s:", line_unicode, 3) == 0) {
            toks = wcstok(line_unicode+3, L"|", &buffer);
            id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(name, toks);   
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[0] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[1] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[2] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[3] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[4] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            directions_ids[5] = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(graphic_description_type, toks);            
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(basic_description[0], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(basic_description[1], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(basic_description[2], toks);            
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check_description[0], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check_description[1], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check_description[2], toks);

            i = 0;
            toks = wcstok(NULL, L"|", &buffer);
            while (toks != NULL && i <= MAX_TAGS-SPACE_BASE_TAGS) {
            	if(wcslen(toks) > 3) {
                	tags[i] = game_str_to_tag(toks);
                } else {
                	tags[i] = wcstol(toks, &toks, 10);
                }
                toks = wcstok(NULL, L"|", &buffer);
                i++;
            }

            space = space_create(id);
            if (space == NULL) {
                fclose(file);
                return ERROR;
            }
            
            space_set_name(space, name);            
            for (direction = NORTH; direction <= BELOW; direction++) space_set_direction(space, direction, LINK_BASE_ID+directions_ids[direction]);
            select_space_graphic_description(graphic_description, graphic_description_type);
            space_set_graphic_description(space, graphic_description);
            space_set_basic_description(space, basic_description);
            space_set_check_description(space, check_description);
            for (j = 0; j < i; j++) space_add_tags(space, 1, tags[j]);
            game_add_space(game, space);            
        }
    }  

    if (ferror(file)) {
        fclose(file);        
        return ERROR;
    }

    fclose(file);

    return OK;
}

/*This function is used to load the players from the given file. It works side by side with game create from file.*/
STATUS game_management_load_players(Game *game, char *filename) {
    FILE *file = NULL;
    wchar_t line_unicode[WORD_SIZE];
    wchar_t name[WORD_SIZE];
    wchar_t graphic_description[WORD_SIZE];
    wchar_t *toks = NULL;
    wchar_t *buffer;
    Id id = NO_ID;
    int inventory_size = 0;
    Id location = NO_ID;
    Player *player = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgetws(line_unicode, WORD_SIZE, file)) {
        if (wcsncmp(L"#p:", line_unicode, 3) == 0) {
            toks = wcstok(line_unicode+3, L"|", &buffer);
            id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(name, toks);
            toks = wcstok(NULL, L"|", &buffer);
            location = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            inventory_size = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(graphic_description, toks);

            player = player_create(PLAYER_BASE_ID+id, inventory_size);
            if (player == NULL) {
                fclose(file);
                return ERROR;
            }
                
            player_set_name(player, name);
            player_set_graphic_description(player, graphic_description);
            game_add_player(game, player, location);
            
        }
    }

    if (ferror(file)) {
        fclose(file);
        return ERROR;
    }

    fclose(file);

    return OK;
}

/*This function is used to load the objects from the given file. It works side by side with game create from file.*/
STATUS game_management_load_objects(Game *game, char *filename) {
    FILE *file = NULL;
    wchar_t line_unicode[WORD_SIZE];
    wchar_t name[WORD_SIZE];
    wchar_t check[MAX_TDESC_R][MAX_TDESC_C];
    wchar_t alt_check[MAX_TDESC_R][MAX_TDESC_C];
    wchar_t *toks = NULL;
    wchar_t *buffer;
    TAG tags[MAX_TAGS];
    Id id = NO_ID;
    Id location = NO_ID;
    Object *object = NULL;
    int i, j;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgetws(line_unicode, WORD_SIZE, file)) {
        if (wcsncmp(L"#o:", line_unicode, 3) == 0) {
            toks = wcstok(line_unicode+3, L"|", &buffer);
            id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(name, toks);
            toks = wcstok(NULL, L"|", &buffer);
            location = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check[0], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check[1], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(check[2], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(alt_check[0], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(alt_check[1], toks);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(alt_check[2], toks);

            i = 0;
            toks = wcstok(NULL, L"|", &buffer);
            while (toks != NULL && i <= MAX_TAGS-OBJECT_BASE_TAGS) {
                if(wcslen(toks) > 3) {
                	tags[i] = game_str_to_tag(toks);
                } else {
                	tags[i] = wcstol(toks, &toks, 10);
                }
                toks = wcstok(NULL, L"|", &buffer);
                i++;
            }

            object = object_create(OBJECT_BASE_ID+id);
            if (object == NULL) {
                fclose(file);
                return ERROR;
            }

            object_set_name(object, name);
            object_set_check(object, check);
            object_set_alt_check(object, alt_check);
            for (j = 0; j < i; j++) object_add_tags(object, 1, tags[j]);
            game_add_object(game, object, location);            
        }
    }

    if (ferror(file)) {
        fclose(file);
        return ERROR;
    }

    fclose(file);

    return OK;
}

/*This function is used to load the links from the given file. It works side by side with game create from file.*/
STATUS game_management_load_links(Game *game, char *filename) {
    FILE *file = NULL;
    wchar_t line_unicode[WORD_SIZE];
    wchar_t name[WORD_SIZE];
    wchar_t *toks = NULL;
    wchar_t *buffer;
    Id id = NO_ID;
    Id space1_id = NO_ID;
    Id space2_id = NO_ID;
    LINK_STATUS status;
    TAG opener = NO_TAG;
    Link *link = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgetws(line_unicode, WORD_SIZE, file)) {
        if (wcsncmp(L"#l:", line_unicode, 3) == 0) {
            toks = wcstok(line_unicode+3, L"|", &buffer);
            id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            wcscpy(name, toks);
            toks = wcstok(NULL, L"|", &buffer);
            space1_id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            space2_id = wcstol(toks, &toks, 10);
            toks = wcstok(NULL, L"|", &buffer);
            if (wcscmp(toks, L"OPEN") == 0) {
                status = OPEN;
            } else if (wcscmp(toks, L"CLOSED") == 0) {
                status = CLOSED;
            } else if (wcstol(toks, &toks, 10) == CLOSED) {
                status = CLOSED;
            } else {
            	status = OPEN;
            }
            toks = wcstok(NULL, L"|", &buffer);
            opener = game_str_to_tag(toks);

            link = link_create(LINK_BASE_ID+id);
            if (link == NULL) {
                fclose(file);
                return ERROR;
            }

            link_set_name(link, name);
            link_add_space(link, space1_id+SPACE_BASE_ID);
            link_add_space(link, space2_id+SPACE_BASE_ID);
            link_set_status(link, status);
            link_set_opener(link, opener);
            game_add_link(game, link);            
        }
    }

    if (ferror(file)) {
        fclose(file);
        return ERROR;
    }

    fclose(file);

    return OK;
}

STATUS game_management_load(Game *game, char *filename){
    nfdchar_t *outPath = NULL;
    char aux[256];

    if (game == NULL || filename == NULL){
        return ERROR;
    }

    strcpy(aux, filename);

    if (SAFE_MODE) {
        printf("You are using the Safe Mode, some features are disabled, we are loading the initial datafile.");
        strcpy(aux, "./datafiles/data.dat");
    } else {
        if (strcmp(aux, "NO_INFO") == 0) {
            if (NFD_OpenDialog( NULL, "./save_games/", &outPath ) == NFD_OKAY) {
                strcpy(aux, (char *) outPath);
                free(outPath);
            }
            else {
                free(outPath);
                return ERROR;
            }
        }
    }

    if (game_create_from_file(game, aux) == ERROR){
        return ERROR;
    } 

    return OK;
}

STATUS game_management_save(Game *game, char *filename){
    FILE *f = NULL;
    char aux[WORD_SIZE];

    if (game == NULL){
        return ERROR;
    }

    strcpy(aux, "./save_games/");

    if (filename == NULL || strcmp(filename, "NO_INFO") == 0){
        strcat(aux, "autosave");
    } else {
        strcat(aux, filename);
    }

    strcat(aux, ".game");

    f = fopen(aux, "w");
    if (f == NULL){
        return ERROR;
    }

    game_print_data(f, game);
    
    fclose(f);

    return OK;
}

void select_space_graphic_description(wchar_t graphic_description[MAX_GDESC_R][MAX_GDESC_C], wchar_t graphic_description_type[WORD_SIZE]) {
    if (wcscmp(graphic_description_type, L"STD_ROOM") == 0) {
        wcscpy(graphic_description[0], STD_ROOM_0);
        wcscpy(graphic_description[1], STD_ROOM_1);
        wcscpy(graphic_description[2], STD_ROOM_2);
        wcscpy(graphic_description[3], STD_ROOM_3);
        wcscpy(graphic_description[4], STD_ROOM_4);
        wcscpy(graphic_description[5], STD_ROOM_5);
        wcscpy(graphic_description[6], STD_ROOM_6);
        wcscpy(graphic_description[7], STD_ROOM_7);
        wcscpy(graphic_description[8], STD_ROOM_8);
        wcscpy(graphic_description[9], STD_ROOM_9);
    } else if (wcscmp(graphic_description_type, L"HALLWAY_1") == 0) {
        wcscpy(graphic_description[0], HALLWAY_1_0);
        wcscpy(graphic_description[1], HALLWAY_1_1);
        wcscpy(graphic_description[2], HALLWAY_1_2);
        wcscpy(graphic_description[3], HALLWAY_1_3);
        wcscpy(graphic_description[4], HALLWAY_1_4);
        wcscpy(graphic_description[5], HALLWAY_1_5);
        wcscpy(graphic_description[6], HALLWAY_1_6);
        wcscpy(graphic_description[7], HALLWAY_1_7);
        wcscpy(graphic_description[8], HALLWAY_1_8);
        wcscpy(graphic_description[9], HALLWAY_1_9);
    } else if (wcscmp(graphic_description_type, L"HALLWAY_2") == 0) {
        wcscpy(graphic_description[0], HALLWAY_2_0);
        wcscpy(graphic_description[1], HALLWAY_2_1);
        wcscpy(graphic_description[2], HALLWAY_2_2);
        wcscpy(graphic_description[3], HALLWAY_2_3);
        wcscpy(graphic_description[4], HALLWAY_2_4);
        wcscpy(graphic_description[5], HALLWAY_2_5);
        wcscpy(graphic_description[6], HALLWAY_2_6);
        wcscpy(graphic_description[7], HALLWAY_2_7);
        wcscpy(graphic_description[8], HALLWAY_2_8);
        wcscpy(graphic_description[9], HALLWAY_2_9);
    } else if (wcscmp(graphic_description_type, L"HALLWAY_3") == 0) {
        wcscpy(graphic_description[0], HALLWAY_3_0);
        wcscpy(graphic_description[1], HALLWAY_3_1);
        wcscpy(graphic_description[2], HALLWAY_3_2);
        wcscpy(graphic_description[3], HALLWAY_3_3);
        wcscpy(graphic_description[4], HALLWAY_3_4);
        wcscpy(graphic_description[5], HALLWAY_3_5);
        wcscpy(graphic_description[6], HALLWAY_3_6);
        wcscpy(graphic_description[7], HALLWAY_3_7);
        wcscpy(graphic_description[8], HALLWAY_3_8);
        wcscpy(graphic_description[9], HALLWAY_3_9);
    } else if (wcscmp(graphic_description_type, L"HALLWAY_4") == 0) {
        wcscpy(graphic_description[0], HALLWAY_4_0);
        wcscpy(graphic_description[1], HALLWAY_4_1);
        wcscpy(graphic_description[2], HALLWAY_4_2);
        wcscpy(graphic_description[3], HALLWAY_4_3);
        wcscpy(graphic_description[4], HALLWAY_4_4);
        wcscpy(graphic_description[5], HALLWAY_4_5);
        wcscpy(graphic_description[6], HALLWAY_4_6);
        wcscpy(graphic_description[7], HALLWAY_4_7);
        wcscpy(graphic_description[8], HALLWAY_4_8);
        wcscpy(graphic_description[9], HALLWAY_4_9);
    } else if (wcscmp(graphic_description_type, L"HIBERNATION_ROOM") == 0) {
        wcscpy(graphic_description[0], HIBERNATION_ROOM_0);
        wcscpy(graphic_description[1], HIBERNATION_ROOM_1);
        wcscpy(graphic_description[2], HIBERNATION_ROOM_2);
        wcscpy(graphic_description[3], HIBERNATION_ROOM_3);
        wcscpy(graphic_description[4], HIBERNATION_ROOM_4);
        wcscpy(graphic_description[5], HIBERNATION_ROOM_5);
        wcscpy(graphic_description[6], HIBERNATION_ROOM_6);
        wcscpy(graphic_description[7], HIBERNATION_ROOM_7);
        wcscpy(graphic_description[8], HIBERNATION_ROOM_8);
        wcscpy(graphic_description[9], HIBERNATION_ROOM_9);
    } else if (wcscmp(graphic_description_type, L"STAIRS_ROOM_UP") == 0) {
        wcscpy(graphic_description[0], STAIRS_ROOM_UP_0);
        wcscpy(graphic_description[1], STAIRS_ROOM_UP_1);
        wcscpy(graphic_description[2], STAIRS_ROOM_UP_2);
        wcscpy(graphic_description[3], STAIRS_ROOM_UP_3);
        wcscpy(graphic_description[4], STAIRS_ROOM_UP_4);
        wcscpy(graphic_description[5], STAIRS_ROOM_UP_5);
        wcscpy(graphic_description[6], STAIRS_ROOM_UP_6);
        wcscpy(graphic_description[7], STAIRS_ROOM_UP_7);
        wcscpy(graphic_description[8], STAIRS_ROOM_UP_8);
        wcscpy(graphic_description[9], STAIRS_ROOM_UP_9);
    } else if (wcscmp(graphic_description_type, L"ELEVATOR_HALL") == 0) {
        wcscpy(graphic_description[0], ELEVATOR_HALL_0);
        wcscpy(graphic_description[1], ELEVATOR_HALL_1);
        wcscpy(graphic_description[2], ELEVATOR_HALL_2);
        wcscpy(graphic_description[3], ELEVATOR_HALL_3);
        wcscpy(graphic_description[4], ELEVATOR_HALL_4);
        wcscpy(graphic_description[5], ELEVATOR_HALL_5);
        wcscpy(graphic_description[6], ELEVATOR_HALL_6);
        wcscpy(graphic_description[7], ELEVATOR_HALL_7);
        wcscpy(graphic_description[8], ELEVATOR_HALL_8);
        wcscpy(graphic_description[9], ELEVATOR_HALL_9);
    } else if (wcscmp(graphic_description_type, L"STAIRS_ROOM_DOWN") == 0) {
        wcscpy(graphic_description[0], STAIRS_ROOM_DOWN_0);
        wcscpy(graphic_description[1], STAIRS_ROOM_DOWN_1);
        wcscpy(graphic_description[2], STAIRS_ROOM_DOWN_2);
        wcscpy(graphic_description[3], STAIRS_ROOM_DOWN_3);
        wcscpy(graphic_description[4], STAIRS_ROOM_DOWN_4);
        wcscpy(graphic_description[5], STAIRS_ROOM_DOWN_5);
        wcscpy(graphic_description[6], STAIRS_ROOM_DOWN_6);
        wcscpy(graphic_description[7], STAIRS_ROOM_DOWN_7);
        wcscpy(graphic_description[8], STAIRS_ROOM_DOWN_8);
        wcscpy(graphic_description[9], STAIRS_ROOM_DOWN_9);
    } else if (wcscmp(graphic_description_type, L"ELEVATOR_11") == 0) {
        wcscpy(graphic_description[0], ELEVATOR_11_0);
        wcscpy(graphic_description[1], ELEVATOR_11_1);
        wcscpy(graphic_description[2], ELEVATOR_11_2);
        wcscpy(graphic_description[3], ELEVATOR_11_3);
        wcscpy(graphic_description[4], ELEVATOR_11_4);
        wcscpy(graphic_description[5], ELEVATOR_11_5);
        wcscpy(graphic_description[6], ELEVATOR_11_6);
        wcscpy(graphic_description[7], ELEVATOR_11_7);
        wcscpy(graphic_description[8], ELEVATOR_11_8);
        wcscpy(graphic_description[9], ELEVATOR_11_9);
    } else if (wcscmp(graphic_description_type, L"ELEVATOR_12") == 0) {
        wcscpy(graphic_description[0], ELEVATOR_12_0);
        wcscpy(graphic_description[1], ELEVATOR_12_1);
        wcscpy(graphic_description[2], ELEVATOR_12_2);
        wcscpy(graphic_description[3], ELEVATOR_12_3);
        wcscpy(graphic_description[4], ELEVATOR_12_4);
        wcscpy(graphic_description[5], ELEVATOR_12_5);
        wcscpy(graphic_description[6], ELEVATOR_12_6);
        wcscpy(graphic_description[7], ELEVATOR_12_7);
        wcscpy(graphic_description[8], ELEVATOR_12_8);
        wcscpy(graphic_description[9], ELEVATOR_12_9);
    } else if (wcscmp(graphic_description_type, L"WAREHOUSE") == 0) {
        wcscpy(graphic_description[0], WAREHOUSE_0);
        wcscpy(graphic_description[1], WAREHOUSE_1);
        wcscpy(graphic_description[2], WAREHOUSE_2);
        wcscpy(graphic_description[3], WAREHOUSE_3);
        wcscpy(graphic_description[4], WAREHOUSE_4);
        wcscpy(graphic_description[5], WAREHOUSE_5);
        wcscpy(graphic_description[6], WAREHOUSE_6);
        wcscpy(graphic_description[7], WAREHOUSE_7);
        wcscpy(graphic_description[8], WAREHOUSE_8);
        wcscpy(graphic_description[9], WAREHOUSE_9);
    } else if (wcscmp(graphic_description_type, L"LARGE_WAREHOUSE") == 0) {
        wcscpy(graphic_description[0], LARGE_WAREHOUSE_0);
        wcscpy(graphic_description[1], LARGE_WAREHOUSE_1);
        wcscpy(graphic_description[2], LARGE_WAREHOUSE_2);
        wcscpy(graphic_description[3], LARGE_WAREHOUSE_3);
        wcscpy(graphic_description[4], LARGE_WAREHOUSE_4);
        wcscpy(graphic_description[5], LARGE_WAREHOUSE_5);
        wcscpy(graphic_description[6], LARGE_WAREHOUSE_6);
        wcscpy(graphic_description[7], LARGE_WAREHOUSE_7);
        wcscpy(graphic_description[8], LARGE_WAREHOUSE_8);
        wcscpy(graphic_description[9], LARGE_WAREHOUSE_9);
    } else if (wcscmp(graphic_description_type, L"STAIRS_ROOM_UP_2") == 0) {
        wcscpy(graphic_description[0], STAIRS_ROOM_UP_2_0);
        wcscpy(graphic_description[1], STAIRS_ROOM_UP_2_1);
        wcscpy(graphic_description[2], STAIRS_ROOM_UP_2_2);
        wcscpy(graphic_description[3], STAIRS_ROOM_UP_2_3);
        wcscpy(graphic_description[4], STAIRS_ROOM_UP_2_4);
        wcscpy(graphic_description[5], STAIRS_ROOM_UP_2_5);
        wcscpy(graphic_description[6], STAIRS_ROOM_UP_2_6);
        wcscpy(graphic_description[7], STAIRS_ROOM_UP_2_7);
        wcscpy(graphic_description[8], STAIRS_ROOM_UP_2_8);
        wcscpy(graphic_description[9], STAIRS_ROOM_UP_2_9);
    } else if (wcscmp(graphic_description_type, L"MECHANICAL_ROOM") == 0) {
        wcscpy(graphic_description[0], MECHANICAL_ROOM_0);
        wcscpy(graphic_description[1], MECHANICAL_ROOM_1);
        wcscpy(graphic_description[2], MECHANICAL_ROOM_2);
        wcscpy(graphic_description[3], MECHANICAL_ROOM_3);
        wcscpy(graphic_description[4], MECHANICAL_ROOM_4);
        wcscpy(graphic_description[5], MECHANICAL_ROOM_5);
        wcscpy(graphic_description[6], MECHANICAL_ROOM_6);
        wcscpy(graphic_description[7], MECHANICAL_ROOM_7);
        wcscpy(graphic_description[8], MECHANICAL_ROOM_8);
        wcscpy(graphic_description[9], MECHANICAL_ROOM_9);
    } else if (wcscmp(graphic_description_type, L"HALL") == 0) {
        wcscpy(graphic_description[0], HALL_0);
        wcscpy(graphic_description[1], HALL_1);
        wcscpy(graphic_description[2], HALL_2);
        wcscpy(graphic_description[3], HALL_3);
        wcscpy(graphic_description[4], HALL_4);
        wcscpy(graphic_description[5], HALL_5);
        wcscpy(graphic_description[6], HALL_6);
        wcscpy(graphic_description[7], HALL_7);
        wcscpy(graphic_description[8], HALL_8);
        wcscpy(graphic_description[9], HALL_9);
    } else if (wcscmp(graphic_description_type, L"KEY_ROOM") == 0) {
        wcscpy(graphic_description[0], KEY_ROOM_0);
        wcscpy(graphic_description[1], KEY_ROOM_1);
        wcscpy(graphic_description[2], KEY_ROOM_2);
        wcscpy(graphic_description[3], KEY_ROOM_3);
        wcscpy(graphic_description[4], KEY_ROOM_4);
        wcscpy(graphic_description[5], KEY_ROOM_5);
        wcscpy(graphic_description[6], KEY_ROOM_6);
        wcscpy(graphic_description[7], KEY_ROOM_7);
        wcscpy(graphic_description[8], KEY_ROOM_8);
        wcscpy(graphic_description[9], KEY_ROOM_9);
    } else if (wcscmp(graphic_description_type, L"RECEPTION") == 0) {
        wcscpy(graphic_description[0], RECEPTION_0);
        wcscpy(graphic_description[1], RECEPTION_1);
        wcscpy(graphic_description[2], RECEPTION_2);
        wcscpy(graphic_description[3], RECEPTION_3);
        wcscpy(graphic_description[4], RECEPTION_4);
        wcscpy(graphic_description[5], RECEPTION_5);
        wcscpy(graphic_description[6], RECEPTION_6);
        wcscpy(graphic_description[7], RECEPTION_7);
        wcscpy(graphic_description[8], RECEPTION_8);
        wcscpy(graphic_description[9], RECEPTION_9);
    } else if (wcscmp(graphic_description_type, L"WASHROOM") == 0) {
        wcscpy(graphic_description[0], WASHROOM_0);
        wcscpy(graphic_description[1], WASHROOM_1);
        wcscpy(graphic_description[2], WASHROOM_2);
        wcscpy(graphic_description[3], WASHROOM_3);
        wcscpy(graphic_description[4], WASHROOM_4);
        wcscpy(graphic_description[5], WASHROOM_5);
        wcscpy(graphic_description[6], WASHROOM_6);
        wcscpy(graphic_description[7], WASHROOM_7);
        wcscpy(graphic_description[8], WASHROOM_8);
        wcscpy(graphic_description[9], WASHROOM_9);
    }  else if (wcscmp(graphic_description_type, L"TECHNICAL_LAB_1") == 0) {
        wcscpy(graphic_description[0], TECHNICAL_LAB_1_0);
        wcscpy(graphic_description[1], TECHNICAL_LAB_1_1);
        wcscpy(graphic_description[2], TECHNICAL_LAB_1_2);
        wcscpy(graphic_description[3], TECHNICAL_LAB_1_3);
        wcscpy(graphic_description[4], TECHNICAL_LAB_1_4);
        wcscpy(graphic_description[5], TECHNICAL_LAB_1_5);
        wcscpy(graphic_description[6], TECHNICAL_LAB_1_6);
        wcscpy(graphic_description[7], TECHNICAL_LAB_1_7);
        wcscpy(graphic_description[8], TECHNICAL_LAB_1_8);
        wcscpy(graphic_description[9], TECHNICAL_LAB_1_9);
    }  else if (wcscmp(graphic_description_type, L"TECHNICAL_LAB_2") == 0) {
        wcscpy(graphic_description[0], TECHNICAL_LAB_2_0);
        wcscpy(graphic_description[1], TECHNICAL_LAB_2_1);
        wcscpy(graphic_description[2], TECHNICAL_LAB_2_2);
        wcscpy(graphic_description[3], TECHNICAL_LAB_2_3);
        wcscpy(graphic_description[4], TECHNICAL_LAB_2_4);
        wcscpy(graphic_description[5], TECHNICAL_LAB_2_5);
        wcscpy(graphic_description[6], TECHNICAL_LAB_2_6);
        wcscpy(graphic_description[7], TECHNICAL_LAB_2_7);
        wcscpy(graphic_description[8], TECHNICAL_LAB_2_8);
        wcscpy(graphic_description[9], TECHNICAL_LAB_2_9);
    }  else if (wcscmp(graphic_description_type, L"LARGE_LAB") == 0) {
        wcscpy(graphic_description[0], LARGE_LAB_0);
        wcscpy(graphic_description[1], LARGE_LAB_1);
        wcscpy(graphic_description[2], LARGE_LAB_2);
        wcscpy(graphic_description[3], LARGE_LAB_3);
        wcscpy(graphic_description[4], LARGE_LAB_4);
        wcscpy(graphic_description[5], LARGE_LAB_5);
        wcscpy(graphic_description[6], LARGE_LAB_6);
        wcscpy(graphic_description[7], LARGE_LAB_7);
        wcscpy(graphic_description[8], LARGE_LAB_8);
        wcscpy(graphic_description[9], LARGE_LAB_9);
    }  else if (wcscmp(graphic_description_type, L"TRANS_LAB") == 0) {
        wcscpy(graphic_description[0], TRANS_LAB_0);
        wcscpy(graphic_description[1], TRANS_LAB_1);
        wcscpy(graphic_description[2], TRANS_LAB_2);
        wcscpy(graphic_description[3], TRANS_LAB_3);
        wcscpy(graphic_description[4], TRANS_LAB_4);
        wcscpy(graphic_description[5], TRANS_LAB_5);
        wcscpy(graphic_description[6], TRANS_LAB_6);
        wcscpy(graphic_description[7], TRANS_LAB_7);
        wcscpy(graphic_description[8], TRANS_LAB_8);
        wcscpy(graphic_description[9], TRANS_LAB_9);
    }  else if (wcscmp(graphic_description_type, L"POWER_LAB") == 0) {
        wcscpy(graphic_description[0], POWER_LAB_0);
        wcscpy(graphic_description[1], POWER_LAB_1);
        wcscpy(graphic_description[2], POWER_LAB_2);
        wcscpy(graphic_description[3], POWER_LAB_3);
        wcscpy(graphic_description[4], POWER_LAB_4);
        wcscpy(graphic_description[5], POWER_LAB_5);
        wcscpy(graphic_description[6], POWER_LAB_6);
        wcscpy(graphic_description[7], POWER_LAB_7);
        wcscpy(graphic_description[8], POWER_LAB_8);
        wcscpy(graphic_description[9], POWER_LAB_9);
    }  else if (wcscmp(graphic_description_type, L"POWER_INFO") == 0) {
        wcscpy(graphic_description[0], POWER_INFO_0);
        wcscpy(graphic_description[1], POWER_INFO_1);
        wcscpy(graphic_description[2], POWER_INFO_2);
        wcscpy(graphic_description[3], POWER_INFO_3);
        wcscpy(graphic_description[4], POWER_INFO_4);
        wcscpy(graphic_description[5], POWER_INFO_5);
        wcscpy(graphic_description[6], POWER_INFO_6);
        wcscpy(graphic_description[7], POWER_INFO_7);
        wcscpy(graphic_description[8], POWER_INFO_8);
        wcscpy(graphic_description[9], POWER_INFO_9);
    } else {
        wcscpy(graphic_description[0], ERROR_ROOM_0);
        wcscpy(graphic_description[1], ERROR_ROOM_1);
        wcscpy(graphic_description[2], ERROR_ROOM_2);
        wcscpy(graphic_description[3], ERROR_ROOM_3);
        wcscpy(graphic_description[4], ERROR_ROOM_4);
        wcscpy(graphic_description[5], ERROR_ROOM_5);
        wcscpy(graphic_description[6], ERROR_ROOM_6);
        wcscpy(graphic_description[7], ERROR_ROOM_7);
        wcscpy(graphic_description[8], ERROR_ROOM_8);
        wcscpy(graphic_description[9], ERROR_ROOM_9);
    }
}