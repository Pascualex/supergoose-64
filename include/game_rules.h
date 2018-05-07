/**
 * @brief               It implements rules for the game.
 * @file                game_rules.h
 * @author              Víctor Yrazusta
 * @version             1.0
 * @date                05-05-2018 (creation)
 * @copyright           GNU Public License
 */

#ifndef GAMERULES_H
#define GAMERULES_H

#include "types.h"
#include "../include/game.h"
#include "../include/command.h"

/**
 * @name 		game_rules_update
 * @author 		Víctor Yrazusta
 * @version             1.0
 * @date		05-05-2018
 * @brief 		Applies rules to the game.
 * @param 		Game* -> a game in which different rules will be applied.
 * @param 		Command* -> the last command introduced.
 * @return		A RULES_STATUS which indicates what rules have been applied.
 */
RULES_STATUS game_rules_update(Game *game, Command *command);

#endif
