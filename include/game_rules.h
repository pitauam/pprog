/**
 * @brief It defines the gamerules module
 *
 * @file game_rules.h
 * @version 0
 * @date 28-04-2026
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"
#include "types.h"

#define MAX_ARG 32 /*maximum number of characters for the argument*/

typedef enum {UNKNOWN_CMD = -1, TELEPORT, RANDOM_DAMAGE, RANDOM_DROP} CommandRules; /*different commands available*/

/**
 * @brief reads the command and finds what to do in order to update the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_update(Game *game);

#endif