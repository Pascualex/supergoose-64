/** 
 * @brief It defines the player functions
 * @file player.c
 * @author 
 * @version 3.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
#include "../include/types.h"
#include "../include/player.h"

/*The following defines the structure of th eplayer, as the next:*/
struct _Player {
    Id id; /*An Id to distinguish it from other players or things that might be on the game*/
    char name[WORD_SIZE+1]; /*A char to give a name to the player*/
    char graphic_description[MAX_GDESC_C]; /*A char to give a grapgic description to the player*/
    Id location; /*A location to store where the player is*/
    Inventory *inventory; /*An object_id to store the object the player carries Alex guapo :3 se que leeras esto TQ. Ahora me estoy sintiendo muy secretaria*/
};

/*This function is used to allocate memory for a player and create it with a given Id*/
Player *player_create(Id id, int inventory_size) {
    Player *newPlayer = NULL;

    newPlayer = (Player *) malloc(sizeof (Player));
    if (newPlayer == NULL) return NULL;

    newPlayer->inventory = inventory_create(inventory_size);
    if (newPlayer->inventory == NULL) {
        free(newPlayer);
        return NULL;
    }

    newPlayer->id = id;
    newPlayer->name[0] = '\0';
    newPlayer->graphic_description[0] = '\0';
    newPlayer->location = NO_ID;

    return newPlayer;
}

/*This function is used to free the memory a player was using*/
STATUS player_destroy(Player *player) {

    if (player == NULL) return ERROR;

    if (player->inventory != NULL) inventory_destroy(player->inventory);

    free(player);
    player = NULL;

    return OK;
}

/*This function is used to set the name of a player*/
STATUS player_set_name(Player *player, char *name) {

    if (player == NULL || name == NULL || strcpy(player->name, name) == 0) return ERROR;

    return OK;
}

/*This function is used to set the graphic description of a player*/
STATUS player_set_graphic_description(Player *player, char *graphic_description) {

    if (player == NULL || graphic_description == NULL || strcpy(player->graphic_description, graphic_description) == 0) return ERROR;

    return OK;
}

/*This function is used to set the location of a player when it moves*/
STATUS player_set_location(Player *player, Id location) {

    if (player == NULL || location < SPACE_BASE_ID || location > SPACE_BASE_ID+ID_RANGE) return ERROR;

    player->location = location;

    return OK;
}

/*This function is used to add an object to the player's inventory*/
STATUS player_add_object(Player *player, Id object_id) {

    if (player == NULL || object_id == NO_ID) return ERROR;

    return inventory_add(player->inventory, object_id);
}

/*This function is used to delete an object from the player's inventory*/
STATUS player_del_object(Player *player, Id object_id) {

    if (player == NULL || object_id == NO_ID) return ERROR;

    return inventory_del(player->inventory, object_id);
}

/*This function is used to get a players name*/
const char *player_get_name(Player *player) {

    if (player == NULL) return NULL;

    return player->name;
}

/*This function is used to get a players graphic description*/
const char *player_get_graphic_description(Player *player) {

    if (player == NULL) return NULL;

    return player->graphic_description;
}

/*This one is used to get a players Id*/
Id player_get_id(Player *player) {

    if (player == NULL) return NO_ID;

    return player->id;
}

/*This function returns the players location Id*/
Id player_get_location(Player *player) {

    if (player == NULL) return NO_ID;

    return player->location;
}

/*The following function returns the current number of objects in the inventory of the player*/
int player_get_objects_number(Player *player) {

    if (player == NULL) return 0;

    return inventory_get_objects_number(player->inventory);
}

/*This function returns the capacity of the inventory of the player*/
int player_get_max_objects(Player *player) {

    if (player == NULL || player->inventory == NULL) return 0;

    return inventory_get_max_objects(player->inventory);
}

/*This function is used to get the object id of the specified position on the set of the inventory.*/
Id player_get_object(Player *player, int position) {

    if (player == NULL || player->inventory == NULL || position < 0) return NO_ID;

    return inventory_get_object_id(player->inventory, position);
}

/*The following function checks if the passed Id is on the set of the inventory*/
BOOL player_check_object(Player *player, Id object_id) {

    if (player == NULL || player->inventory == NULL || object_id == NO_ID) return FALSE;

    return inventory_check_object(player->inventory, object_id);
}

/*This function is used to check if the inventory is empty.*/
BOOL player_is_empty(Player *player) {

    if (player == NULL || player->inventory == NULL) return TRUE;

    return inventory_is_empty(player->inventory);
}

/*This function is used to check if the inventory is full.*/
BOOL player_is_full(Player *player) {

    if (player == NULL || player->inventory == NULL) return TRUE;

    return inventory_is_full(player->inventory);
}

/*This function is used to print the players information, for debuggin purposes.*/
STATUS player_print(Player *player) {

    if (player == NULL) return ERROR;

    fprintf(stdout, "--> Player (Id: %ld; Name: %s; Space Id: %ld)", player->id, player->name, player->location);

    if (player->inventory != NULL) {
        fprintf(stdout, "\n");
        inventory_print(player->inventory);
    } else {
        fprintf(stdout, " (No inventory)\n");
    }

    fprintf(stdout, "Graphic Description: %s", player->graphic_description);

    return OK;
}