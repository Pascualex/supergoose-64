/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
/**/

#include "../include/game.h"
#include "../include/game_reader.h"

/*This function is used to load the spaces from the given file. It works side by side with game create from file.*/
STATUS game_reader_load_spaces(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char graphic_description[MAX_GDESC_R][MAX_GDESC_C];
    char basic_description[MAX_TDESC_R][MAX_TDESC_C];
    char check_description[MAX_TDESC_R][MAX_TDESC_C];
    char *toks = NULL;
    Id id, directions_ids[6];
    Space *space = NULL;
    DIRECTION direction;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line+3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            directions_ids[0] = atol(toks);
            toks = strtok(NULL, "|");
            directions_ids[1] = atol(toks);
            toks = strtok(NULL, "|");
            directions_ids[2] = atol(toks);
            toks = strtok(NULL, "|");
            directions_ids[3] = atol(toks);
            toks = strtok(NULL, "|");
            directions_ids[4] = atol(toks);
            toks = strtok(NULL, "|");
            directions_ids[5] = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[0], toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[1], toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[2], toks);
            toks = strtok(NULL, "|");
            strcpy(basic_description[0], toks);
            toks = strtok(NULL, "|");
            strcpy(basic_description[1], toks);
            toks = strtok(NULL, "|");
            strcpy(basic_description[2], toks);            
            toks = strtok(NULL, "|");
            strcpy(check_description[0], toks);
            toks = strtok(NULL, "|");
            strcpy(check_description[1], toks);
            toks = strtok(NULL, "|");
            strcpy(check_description[2], toks);

            space = space_create(id);
            if (space == NULL) {
                fclose(file);        
                return ERROR;
            }
            
            space_set_name(space, name);
            for (direction = NORTH; direction <= BELOW; direction++) space_set_direction(space, direction, LINK_BASE_ID+directions_ids[direction]);
            space_set_graphic_description(space, graphic_description);
            space_set_basic_description(space, basic_description);
            space_set_check_description(space, check_description);
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
STATUS game_reader_load_players(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char graphic_description[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID;
    int inventory_size = 0;
    Id location = NO_ID;
    Player *player = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#p:", line, 3) == 0) {
            toks = strtok(line+3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location = atol(toks);
            toks = strtok(NULL, "|");
            inventory_size = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description, toks);

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
STATUS game_reader_load_objects(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char check[MAX_TDESC_R][MAX_TDESC_C];
    char *toks = NULL;
    Id id = NO_ID;
    Id location = NO_ID;
    Object *object = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line+3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(check[0], toks);
            toks = strtok(NULL, "|");
            strcpy(check[1], toks);
            toks = strtok(NULL, "|");
            strcpy(check[2], toks);

            object = object_create(OBJECT_BASE_ID+id);
            if (object == NULL) {
                fclose(file);
                return ERROR;
            }

            object_set_name(object, name);
            object_set_check(object, check);
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
STATUS game_reader_load_links(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID;
    Id space1_id = NO_ID;
    Id space2_id = NO_ID;
    LINK_STATUS status;
    Link *link = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#l:", line, 3) == 0) {
            toks = strtok(line+3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            space1_id = atol(toks);
            toks = strtok(NULL, "|");
            space2_id = atol(toks);
            toks = strtok(NULL, "|");
            if (!strcmp(toks, "OPEN")) {
                status = OPEN;
            } else {
                status = CLOSED;
            }

            link = link_create(LINK_BASE_ID+id);
            if (link == NULL) {
                fclose(file);
                return ERROR;
            }

            link_set_name(link, name);
            link_add_space(link, space1_id+SPACE_BASE_ID);
            link_add_space(link, space2_id+SPACE_BASE_ID);
            link_set_status(link, status);
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