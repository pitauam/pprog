/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 4
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Opaque Game struct*/
struct _Game {
  Player *player;                             /*!< pointer to the player structure*/
  Object *object[MAX_OBJECTS];                /*!< pointer to the array of objects*/
  int n_objects;                              /*!< number of objects*/
  Character *characters[MAX_CHARACTERS];      /*!< pointer to the array of characters*/
  int n_characters;                           /*!< number of characters*/
  Space *spaces[MAX_SPACES];                  /*!< pointer to the spaces structure*/
  int n_spaces;                               /*!< number of spaces in castle*/
  Command *last_cmd;                          /*!< pointer to the last command executed*/
  Bool finished;                              /*!< whether the game has finished or not*/
  char msg[WORD_SIZE+1];                      /*!< message that will be printed in the description section*/
  char name_msg[WORD_SIZE];                   /*!< name of who is sending the message*/
  Link *link[MAX_LINKS];                      /*!< links between spaces*/
  int n_links;                                /*!< number of links*/
};

/**
   Game interface implementation
*/

Game* game_create() {
  int i;
  Game *game;
  Character *character1;
  Character *character2;

  game = (Game *)calloc(1, sizeof(Game));
  if (!game) {return NULL;}

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++){
    game->link[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->object[i] = NULL;
  }

  game->n_spaces = 0;
  game->n_links = 0;
  game->player = player_create(PLAYER_ID); /*Hard coded value*/
  /*Creates character1*/
  character1 = character_create(CHARACTER1);
  game->characters[0] = character1;
  character_set_name(game->characters[0], "kevin");
  character_set_description(game->characters[0], "O_o");
  character_set_message(game->characters[0], " Hola soy kevin. Necesito tu ayuda, mata a todos los enemigos por mi :)");
  /*Creates character2*/
  character2 = character_create(CHARACTER2);
  game->characters[1] = character2;
  character_set_name(game->characters[1], "Guardia");
  character_set_description(game->characters[1], ">:O");
  character_set_message(game->characters[1], " JASJAJSJAJSJAJ vuelve cuando seas mas fuerte plebeyo");
  character_set_friendly(game->characters[1], FALSE);
  game->last_cmd = command_create();
  game->finished = FALSE;
  game->n_characters = 2;
  game->msg[0] = '\0';
  game->name_msg[0] = '\0';


  return game;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_links; i++) {
    link_destroy(game->link[i]);
  }

  command_destroy(game->last_cmd);
  
  player_destroy(game->player);

  for (i = 0; i < game->n_objects;i++)
  {
    object_destroy(game->object[i]);
  }

  for (i = 0; i < game->n_characters; i++)
  {
    character_destroy(game->characters[i]);
  }

  free(game);

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

Id game_get_object_location(Game *game, Id object_id) 
{
  int i;
  if (!game) {return NO_ID;}
  
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_find_object(game->spaces[i], object_id) == TRUE)
    {
      return game_get_space_id_at(game, i);
    }
  }
  
  return NO_ID; 
}

Status game_set_object_location(Game *game, Id new_space_id, Id object_id) {
  Space *space;

  if (!game || new_space_id == NO_ID || object_id == NO_ID ) return ERROR;

  /* Places the object in the space */
  space = game_get_space(game, new_space_id);
  if (!space) return ERROR;

  
  if (space_add_object(space, object_id) == ERROR) {return ERROR;}

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
  printf("Objects: \n");
  for (i = 0; i < game->n_objects;i++)
  {
    printf("  ");
    object_print(game->object[i]);
  }
  printf("=> Player: \n");
  player_print(game->player);

  printf("Characters: \n");
  for (i = 0; i < game->n_characters;i++)
  {
    printf("  ");
    character_print(game->characters[i]);
  }

  printf("Links: \n");
  for (i = 0; i < game->n_links; i++)
  {
    printf("  ");
    link_print(game->link[i]);
  }

}

Status game_add_space(Game *game, Space *space) {
  if ((!game) || (!space) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}
/*FALTA DOCUMENTAR vvv */

Status game_add_link(Game *game, Link *link) {
  if ((!game) || (!link) || (game->n_links >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_links] = link;
  game->n_links++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Player* game_get_player(Game *game)
{
  if (!game || game->player == NULL) {return NULL;}

  return game->player;
}

Status game_add_object(Game *game, Object *object) {
  if ((!game) || (!object) || (game->n_objects >= MAX_OBJECTS)) {
    return ERROR;
  }

  game->object[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Status game_add_character(Game *game, Character *character) {
  if ((!game) || (!character) || (game->n_characters >= MAX_CHARACTERS)) {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (id == object_get_id(game->object[i])) {
      return game->object[i];
    }
  }

  return NULL;
}

int game_get_number_of_objects(Game *game)
{
  if (!game) {return -1;}

  return game->n_objects;
}

Id game_get_object_id(Game *game, int pos)
{
  if (!game || pos < 0) {return NO_ID;}

  return object_get_id(game->object[pos]);
}

const char * game_get_object_name(Game *game, Object *object) 
{
  if (!game || !object) {return NULL;}

  return object_get_name(object);
}

Id game_get_character_id(Game *game, Id id)
{
  if (!game || id == NO_ID) {return NO_ID;}
 
  return space_get_character(game_get_space(game, id)); 
}

Character *game_get_character(Game *game, Id id)
{
  int i;
  if (!game || id == NO_ID) {return NULL;}

  for (i = 0; i < game->n_characters;i++)
  {
    /*if the id given as an argument is found inside a space*/
    if ((character_get_id(game->characters[i]) == id))
    {
      /*returns the character at the place i in the array, which must have id i*/
      return game->characters[i];
    }
  }
  /*if the character isn't found*/
  return NULL;
}

int game_get_number_of_characters(Game *game)
{
  if (!game) {return -1;}

  return game->n_characters;
}

int game_get_number_of_spaces(Game *game){
  if (!game) {return -1;}

  return game->n_spaces;
}

/*FALTA COMENTAR vvv */

int game_get_number_of_links(Game *game){
  if (!game) {return -1;}

  return game->n_links;
}


Id game_get_character_location(Game *game, Id id){
  int i;

  if (!game || id == NO_ID) {return NO_ID;}
  
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_get_character(game->spaces[i]) == id)
    {
      return game_get_space_id_at(game, i);
    }
  }
  
  return NO_ID; 
}

Status game_set_message(Game *game, const char* message){

  if(!game || message == NULL) {return ERROR;}

  strcpy(game->msg, message);

  return OK;
}

const char* game_get_message(Game *game){
  if(!game) {return NULL;}

  return game->msg;
}

Status game_set_name_message(Game *game, const char* name){

  if(!game || name == NULL) {return ERROR;}

  strcpy(game->name_msg, name);

  return OK;
}

const char* game_get_name_message(Game *game){
  if(!game) {return NULL;}

  return game->name_msg;
}

Id game_get_connection(Game *game, Id id_act, Direction link_direction){
  int i;

  if (!game || id_act == NO_ID ||  link_direction == NO_DIR){
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->link[i]) == id_act)
    {
      if (link_get_direction(game->link[i]) == link_direction)
      {
        return link_get_destination(game->link[i]);
      }
    }
  }

  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id id_act, Direction link_direction){
  int i;

  if (!game || id_act == NO_ID || link_direction == NO_DIR){
    return FALSE;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->link[i]) == id_act)
    {
      if (link_get_direction(game->link[i]) == link_direction)
      {
        return link_get_open(game->link[i]);
      }
    }
  }

  return FALSE;
}