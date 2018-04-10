/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/

#include "../include/game.h"
#include "../include/game_reader.h"

/*This function is used to load the spaces from the given file. It works side by side with game create from file.*/
STATUS game_reader_load_spaces(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char graphic_description[3][8];
    char check[MAX_CHECK_R][MAX_CHECK_C];
    char *toks = NULL;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space *space = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            north = atol(toks);
            toks = strtok(NULL, "|");
            west = atol(toks);
            toks = strtok(NULL, "|");
            south = atol(toks);
            toks = strtok(NULL, "|");
            east = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[0], toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[1], toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description[2], toks);
            toks = strtok(NULL, "|");
            strcpy(check[0], toks);
            toks = strtok(NULL, "|");
            strcpy(check[1], toks);
            toks = strtok(NULL, "|");
            strcpy(check[2], toks);

            space = space_create(id);

            if (space != NULL) {
                space_set_name(space, name);
                space_set_north(space, north + LINK_BASE_ID);
                space_set_west(space, west + LINK_BASE_ID);
                space_set_south(space, south + LINK_BASE_ID);
                space_set_east(space, east + LINK_BASE_ID);
                space_set_graphic_description(space, graphic_description);
                space_set_check(space, check);
                game_add_space(game, space);
            }
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
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location = atol(toks);
            toks = strtok(NULL, "|");
            inventory_size = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(graphic_description, toks);

            player = player_create(PLAYER_BASE_ID + id, inventory_size);
            if (player != NULL) {
                player_set_name(player, name);
                player_set_graphic_description(player, graphic_description);
                game_add_player(game, player, location);
            } else {
                fclose(file);

                return ERROR;
            }
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
    char check[MAX_CHECK_R][MAX_CHECK_C];
    char *toks = NULL;
    Id id = NO_ID;
    Id location = NO_ID;
    Object *object = NULL;

    if (game == NULL || filename == NULL) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
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

            object = object_create(id + OBJECT_BASE_ID);
            if (object != NULL) {
                object_set_name(object, name);
                object_set_check(object, check);
                game_add_object(game, object, location);
            } else {
                fclose(file);

                return ERROR;
            }
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
            toks = strtok(line + 3, "|");
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

            link = link_create(id + LINK_BASE_ID);
            if (link != NULL) {
                link_set_name(link, name);
                link_add_space(link, space1_id + SPACE_BASE_ID);
                link_add_space(link, space2_id + SPACE_BASE_ID);
                link_set_status(link, status);
                game_add_link(game, link);
            } else {
                fclose(file);

                return ERROR;
            }
        }
    }

    if (ferror(file)) {
        fclose(file);

        return ERROR;
    }

    fclose(file);

    return OK;
}