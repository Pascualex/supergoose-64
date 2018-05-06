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
#include "nfd.h"

#define STD_ROOM_GDESC_1 L" ┏━━━┓ "
#define STD_ROOM_GDESC_2 L" ┃   ┃ "
#define STD_ROOM_GDESC_3 L" ┗━━━┛ "
#define ERROR_ROOM_GDESC_1 L" ERROR "
#define ERROR_ROOM_GDESC_2 L" ERROR "
#define ERROR_ROOM_GDESC_3 L" ERROR "

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
            if (wcscmp(graphic_description_type, L"STD_ROOM") == 0) {
                wcscpy(graphic_description[0], STD_ROOM_GDESC_1);
                wcscpy(graphic_description[1], STD_ROOM_GDESC_2);
                wcscpy(graphic_description[2], STD_ROOM_GDESC_3);
            } else {
                wcscpy(graphic_description[0], ERROR_ROOM_GDESC_1);
                wcscpy(graphic_description[1], ERROR_ROOM_GDESC_2);
                wcscpy(graphic_description[2], ERROR_ROOM_GDESC_3);
            }
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

    if (strcmp(aux, "NO_INFO") == 0) {
        if (NFD_OpenDialog( NULL, "./save_games/", &outPath ) == NFD_OKAY) {
            strcpy(aux, (char *) outPath);
        }
        else {
            return ERROR;
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

    if (game == NULL || filename == NULL){
        return ERROR;
    }

    strcpy(aux, "./save_games/");
    strcat(aux, filename);

    f = fopen(aux, "w");
    if (f == NULL){
        return ERROR;
    }

    game_print_data(f, game);
    
    fclose(f);

    return OK;
}