/**
 * @brief               It generates the feedback answers to the actions of the player
 * @file                dialogue.h
 * @author              Alejandro Pascual
 * @version             2.0
 * @date                06-05-2018
 * @copyright           GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "../include/game.h"

/**
 * @name 		dialogue_generate
 * @author 		Alejandro Pascual
 * @version             1.0
 * @date		06-05-2018
 * @brief       It sets the corresponding dialogue text depending on the game state
 * @param       Game* -> the game.
 * @param       whcar_t** -> the dialogue unicode text.
 * @return		Void
 */
void dialogue_generate(Game *game, wchar_t dialogue[MAX_DIA_R][MAX_DIA_C]);

#endif