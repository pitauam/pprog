/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1
 * @date 09-02-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Opaque Game struct*/
struct _Game {
  Player *player;
  Object *object;
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
};

/**
   Game interface implementation
*/

Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = player_create(100); /*Temporary hard-coded values*/
  game->object = object_create(200);
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  command_destroy(game->last_cmd);

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { 
  if(game == NULL || game->player == NULL){
    return NO_ID;
  }

  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID || game == NULL || game->player == NULL) {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Id game_get_object_location(Game *game) 
{
  int i;
  if (!game) {return NO_ID;}
  
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_get_object(game->spaces[i]) != NO_ID)
    {
      return game_get_space_id_at(game, i);
    }
  }
  
  return NO_ID; 
}

Status game_set_object_location(Game *game, Id new_space_id) {
  int i;
  Space *space;

  if (!game || new_space_id == NO_ID) return ERROR;

  /* takes out the object of the space */
  for (i = 0; i < game->n_spaces; i++) {
    space = game->spaces[i];
    if (space_get_object(space) != NO_ID) {
      space_set_object(space, NO_ID);
      break;
    }
  }

  /* Places the object in the new space */
  space = game_get_space(game, new_space_id);
  if (!space) return ERROR;

  space_set_object(space, object_get_id(game->object));

  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

/**
   Implementation of private functions
*/

Status game_add_space(Game *game, Space *space) {
  if ((!space) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Id game_get_player(Game *game)
{
  if (!game || game->player == NULL) {return NO_ID;}

  return game->player;
}

Id game_get_object_at_location(Game *game, Space* space)
{
  if (!game || game->spaces == NULL) {return NO_ID;}

  return game->object;


}