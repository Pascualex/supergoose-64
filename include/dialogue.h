/**
 * @brief               It generates the feedback answers to the actions of the player
 * @file                dialoge.h
 * @author              Alejandro Pascual
 * @version             2.0
 * @date                06-05-2018
 * @copyright           GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "../include/game.h"

void dialogue_generate(Game *game, wchar_t dialogue[MAX_DIA_R][MAX_DIA_C]);

#endif