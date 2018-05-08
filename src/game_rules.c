/**
 * @brief It implements the game rules
 * @file game_rules.c
 * @author Victor Yrazusta
 * @version 1.0
 * @date 05-05-2018
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
/*Own libraries*/
#include "../include/player.h"
#include "../include/game_rules.h"
#include "../include/die.h"
#include "../include/types.h"

RULES_STATUS game_rules_update(Game *game, Command *command) {
	Die *die = NULL;
	Space *failing_space = NULL;
	Id location = NO_ID;
	int j;

	if (game == NULL || game_get_players_number(game) == 0 || command == NULL) return ERROR_RULES;

	location = player_get_location((Player *) game_find(game, PLAYER_BASE_ID+1));

	/* RULE 1 (command_get_command(command) == MOVE && ((!strcasecmp(command_get_info(command), "north") || !strncmp(command_get_info(command), "n", 1)) || ))) {*/
	printf("%d\n", command_get_command(command));
	if (location == HALL_ROOM_ID && command_get_command(command) == PREVIOUS){
		printf("ssss");
		for (j = 0; j < player_get_objects_number((Player *) game_find(game, PLAYER_BASE_ID+1)); j++) {
    		if (object_check_tag((Object *) game_find(game, player_get_object_id((Player *) game_find(game, PLAYER_BASE_ID+1), j)), IS_KEY)) {    			
    			return END1;
    		}
    	}
	}

	/* RULE 2 */
	if (location == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, GEARS_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, FUSE_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, TRANS_CORE_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID) {
		return END2;
	}

	/* RULE 3 */
	if (location == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, GEARS_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, FUSE_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID && object_get_location((Object *) game_find(game, POWER_CORE_ID + OBJECT_BASE_ID)) == TRANS_ROOM_ID) {
		return END3;
	}

	die = die_create(DIE_BASE_ID+1, 2);
	if (die == NULL) return ERROR_RULES;

	/* RULE 4 */
	if (die_roll(die) == 1) {
		die_destroy(die);
		
		failing_space = (Space *) game_find(game, FAILING_SPACE_ID);
		if (failing_space == NULL) {
			return ERROR_RULES;
		}
		
		if (space_check_tag(failing_space, ILLUMINATED)) {
			space_remove_tags(failing_space, 1, ILLUMINATED);
		} else {
			space_add_tags(failing_space, 1, ILLUMINATED);
		}

		return SPACE_ILLUMINATED;
	}

	die_destroy(die);

	return NO_RULE;
}