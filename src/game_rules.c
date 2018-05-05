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
#include <stdlib.h>
/*Own libraries*/
#include "../include/game.h"
#include "../include/game_rules.h"

RULES_STATUS game_rules_update(Game *game) {
	Die *die = NULL;
	Space *failing_space = NULL;

	if (game == NULL || game_get_players_number(game) == 0) return ERROR;

	Die = die_ini(DIE_BASE_ID+1, 2);
	if (die == NULL) return ERROR;

	if (die_roll(die) == 1) {
		
		die_destroy(die);
		
		failing_space = (Space *) game_find(game, FAILING_SPACE_ID);
		if (failing_space == NULL) {
			return ERROR;
		}
		
		if (space_check_tag(failing_space, ILLUMINATED)) {
			space_remove_tag(failing_space, ILLUMINATED);
		} else {
			space_add_tag(failing_space, ILLUMINATED);
		}

		return SPACE_ILLUMINATED;
	}
}