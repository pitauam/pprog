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
/**
 * @brief Game
 *
 * This struct stores all the information related to the game.
 */
struct _Game {
  Player *player[MAX_PLAYERS];                /*!< Pointer to the array of players */
  int n_players;                              /*!< Number of players in the game */
  Object *object[MAX_OBJECTS];                /*!< Pointer to the array of objects */
  int n_objects;                              /*!< Number of objects */
  Character *characters[MAX_CHARACTERS];      /*!< Pointer to the array of characters */
  int n_characters;                           /*!< Number of characters */
  Space *spaces[MAX_SPACES];                  /*!< Pointer to the spaces structure */
  int n_spaces;                               /*!< Number of spaces in castle */ 
  Link *link[MAX_LINKS];                      /*!< Pointer to he array of links between spaces */
  int n_links;                                /*!< Number of links */
  int turn;                                   /*!< Indicates the index of the player that has a turn */
  InterfaceData* interface_data[MAX_PLAYERS]; /*!< Stores the interface data of each player */
};



/**
 * @brief Interface Data
 *
 * This struct stores all the information related to the interface data.
 */
struct _InterfaceData {
  Command *last_cmd;                          /*!< Pointer to the last command executed*/
  Bool finished;                              /*!< Whether the game has finished or not*/
  char msg[WORD_SIZE+1];                      /*!< Message that will be printed in the description section*/
  char name_msg[WORD_SIZE];                   /*!< Name of who is sending the message*/
};

/*
   Game interface implementation
*/

Game* game_create() {
  int i, j;
  Game *game;

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

  for (i = 0; i < MAX_PLAYERS; i++) {
    game->player[i] = NULL;

    game->interface_data[i] = (InterfaceData *)calloc(1, sizeof(InterfaceData));
    if (game->interface_data[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(game->interface_data[j]);
      }
      free(game);
      return NULL;
    }

    game->interface_data[i]->last_cmd = NULL;
    game->interface_data[i]->finished = FALSE;
    game->interface_data[i]->msg[0] = '\0';
    game->interface_data[i]->name_msg[0] = '\0';
  }

  game->n_spaces = 0;
  game->n_players = 0;
  game->n_objects = 0;
  game->n_links = 0;
  game->n_characters = 0;

  game->turn = 0;

  return game;
}

Status game_destroy(Game *game) {
  int i;

  if (!game) {return ERROR;}

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_links; i++) {
    link_destroy(game->link[i]);
  }

  for (i = 0; i < game->n_objects;i++)
  {
    object_destroy(game->object[i]);
  }

  for (i = 0; i < game->n_characters; i++)
  {
    character_destroy(game->characters[i]);
  }

  for (i = 0; i < game->n_players; i++)
  { 
    player_destroy(game->player[i]);
    command_destroy(game->interface_data[i]->last_cmd);
  }

  for (i = 0; i < MAX_PLAYERS; i++) 
  {
    free(game->interface_data[i]);
  }

  free(game);

  return OK;
}

/**
 * Game player functions implementation.
 */

Id game_get_player_location(Game *game) { 
  if(game == NULL || game->player[game->turn] == NULL){
    return NO_ID;
  }

  return player_get_location(game->player[game->turn]);
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID || game == NULL || game->player[game->turn] == NULL) {
    return ERROR;
  }

  return player_set_location(game->player[game->turn], id);
}

Status game_add_player(Game *game, Player *player) {
  if (!game || !player || game->n_players >= MAX_PLAYERS) {
    return ERROR;
  }

  if (game->player[game->n_players] != NULL) {
    player_destroy(game->player[game->n_players]);
  }

  game->player[game->n_players] = player;
  
  game->interface_data[game->n_players]->last_cmd = command_create();

  game->n_players++;

  return OK;
}

Player* game_get_player(Game *game)
{
  if (!game || game->player[game->turn] == NULL) {return NULL;}

  return game->player[game->turn];
}


/**
 * Game object functions implementation.
 */

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

Status game_add_object(Game *game, Object *object) {
  if ((!game) || (!object) || (game->n_objects >= MAX_OBJECTS)) {
    return ERROR;
  }

  game->object[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Status game_remove_object(Game *game, Object *object){

  Id obj_id = NO_ID;
  int index = -1;
  int i = 0;

  if(!game || !object){
    return ERROR;
  }

  obj_id = object_get_id(object);
  index = game_get_object_position(game, obj_id);

  if(index == -1){
    return ERROR;
  }

  object_destroy(game->object[index]);
  for (i = index; i < game->n_objects - 1; i++)
  {
    game->object[i] = game->object[i + 1];
  }

  game->n_objects--;
  game->object[game->n_objects] = NULL;
  
  return OK;
}

void game_sort_inventory(Game *game) {
  Player *player = NULL;
  Inventory *inventory = NULL;
  Id ids[MAX_OBJECTS];
  Id key = NO_ID;
  int n_objects = 0, i, j;

  if (!game) {
    return;
  }

  player = game_get_player(game);
  if (!player) {
    return;
  }

  inventory = player_get_inventory(player);
  if (!inventory) {
    return;
  }

  n_objects = inventory_get_n_objects(inventory);
  if (n_objects <= 1 || n_objects > MAX_OBJECTS) {
    return;
  }

  for (i = 0; i < n_objects; i++) {
    ids[i] = inventory_get_object_id(inventory, i);
  }

  for (i = 1; i < n_objects; i++) {
    key = ids[i];
    j = i - 1;

    while (j >= 0 && object_compare(game_get_object(game, ids[j]), game_get_object(game, key)) > 0) {
      ids[j + 1] = ids[j];
      j--;
    }

    ids[j + 1] = key;
  }

  for (i = 0; i < n_objects; i++) {
    inventory_remove_object(inventory, ids[i]);
  }

  for (i = 0; i < n_objects; i++) {
    inventory_add_object(inventory, ids[i]);
  }
}

Object *game_get_object(Game *game, Id id) {
  int i;

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

Id game_get_object_id_at(Game *game, int pos)
{
  if (!game || pos < 0) {return NO_ID;}

  return object_get_id(game->object[pos]);
}

const char *game_get_object_name(Game *game, Object *object) 
{
  if (!game || !object) {return NULL;}

  return object_get_name(object);
}

Object* game_get_object_by_name(Game* game, char* name){
  int i;
  if(!game) return NULL;

  for (i = 0; i < game->n_objects; i++) {
    if (strcmp(name, object_get_name(game->object[i])) == 0) {
      return game->object[i];
    }
  }

  return NULL;
}

int game_get_object_position(Game *game, Id object_id){

  int i = 0;

  if(!game){
    return ERROR;
  }

  for(i = 0; i < game->n_objects; i++){
    if(game_get_object_id_at(game, i) == object_id){
      return i;
    }
  }

  return -1;
}

/**
 * Game character functions implementation.
 */

Status game_add_character(Game *game, Character *character) {
  if ((!game) || (!character) || (game->n_characters >= MAX_CHARACTERS)) {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
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

const char *game_get_character_name(Game *game, Character *chr) 
{
  if (!game || !chr) {return NULL;}

  return character_get_name(chr);
}

int game_get_number_of_characters(Game *game)
{
  if (!game) {return -1;}

  return game->n_characters;
}

int game_get_number_of_players(Game *game)
{
  if (!game) {return -1;}

  return game->n_players;
}

Id game_get_character_id_at(Game *game, int position) {
  if (!game || position < 0)
  {
    return NO_ID;
  }

  return character_get_id(game->characters[position]);
}

Character* game_get_character_by_name(Game* game, char* name){
  int i;
  if(!game) return NULL;

  for (i = 0; i < game->n_characters; i++) {
    if (strcmp(name, character_get_name(game->characters[i])) == 0) {
      return game->characters[i];
    }
  }

  return NULL;
  

}

int game_get_n_followers(Game *game, Player *player){
  int n_followers;
  Character *char_aux = NULL;
  int i;

  if (!game || !player){
    return -1;
  }

  n_followers = 0;
  for (i = 0; i < game_get_number_of_characters(game); i++)
  {
    char_aux = game_get_character(game, game_get_character_id_at(game, i));
    /*if the character is following the current player*/
    if (character_get_following(char_aux) == player_get_id(player))
    {
      n_followers++;
    }
  }

  return n_followers;
}

Id game_get_character_location(Game *game, Id id){
  int i;
  if (!game || id == NO_ID) {return NO_ID;}
  
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_find_character(game->spaces[i], id) == TRUE)
    {
      return game_get_space_id_at(game, i);
    }
  }

  return NO_ID; 
}

Status game_set_character_location(Game *game, Id new_space_id, Id chr_id) {

  if (!game || new_space_id == NO_ID || chr_id == NO_ID)
  {
    return ERROR;
  }

  return space_add_character(game_get_space(game, new_space_id), chr_id);
}

Id game_get_character_id(Game *game, Id space_id) {
  int i;
  Id current_char_id = NO_ID;

  if (!game || space_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_characters; i++) {
    current_char_id = character_get_id(game->characters[i]);
    if (game_get_character_location(game, current_char_id) == space_id) {
      return current_char_id;
    }
  }

  return NO_ID;
}

/**
 * Game space functions implementation.
 */

Status game_add_space(Game *game, Space *space) {
  if ((!game) || (!space) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

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

Id game_get_space_id_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

int game_get_number_of_spaces(Game *game){
  if (!game) {return -1;}

  return game->n_spaces;
}

Id game_get_random_space(Game *game){
  int random_number;
  Id space_id = NO_ID;

  if (!game){
    return NO_ID;
  }

  while (space_id == NO_ID || space_is_discovered(game_get_space(game, space_id)) == FALSE)
  {
    random_number = rand() % game_get_number_of_spaces(game);
    space_id = game_get_space_id_at(game, random_number);
  }
  
  return space_id;
}

/**
 * Game link functions implementation.
 */

Status game_add_link(Game *game, Link *link) {
  if ((!game) || (!link) || (game->n_links >= MAX_SPACES)) {
    return ERROR;
  }

  game->link[game->n_links] = link;
  game->n_links++;

  return OK;
}

Link *game_get_link(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_links; i++) {
    if (id == link_get_id(game->link[i])) {
      return game->link[i];
    }
  }

  return NULL;
}

Id game_get_link_id_at(Game *game, int position) {
  
  if (!game || position < 0 || position > MAX_LINKS)
  {
    return NO_ID;
  }

  return link_get_id(game->link[position]);
}


Link *game_get_link_by_origin_destination(Game *game, Id origin, Id destination) {
  int i;
  Link *aux_link = NULL;

  if (!game || origin == NO_ID || destination == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    aux_link = game_get_link(game, game_get_link_id_at(game, i));
    if (link_get_origin(aux_link) == origin && link_get_destination(aux_link) == destination)
    {
      return aux_link;
    }
  }
  
  return NULL;
}

Link* game_get_link_by_name(Game* game, char* name){
  int i;
  if(!game) return NULL;

  for (i = 0; i < game->n_links; i++) {
    if (strcmp(name, link_get_name(game->link[i])) == 0) {
      return game->link[i];
    }
  }

  return NULL;
}



int game_get_number_of_links(Game *game){
  if (!game) {return -1;}

  return game->n_links;
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

/**
 * Game interface data implementation.
 */

Command* game_get_last_command(Game *game) {
  if (!game || game->turn < 0 || game->turn >= game->n_players) {
    return NULL;
  }

  return game->interface_data[game->turn]->last_cmd; 
}

Status game_set_last_command(Game *game, Command *command) {
  if (!game || game->turn < 0 || game->turn >= MAX_PLAYERS) {
    return ERROR;
  }

  game->interface_data[game->turn]->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) {
  if (!game || game->turn < 0 || game->turn >= game->n_players) {
    return FALSE;
  }

  return game->interface_data[game->turn]->finished;
}

Status game_set_finished(Game *game, Bool finished) {
  if (!game || game->turn < 0 || game->turn >= MAX_PLAYERS) {
    return ERROR;
  }

  game->interface_data[game->turn]->finished = finished;

  return OK;
}

Status game_set_message(Game *game, const char* message){

  if(!game || message == NULL || game->turn < 0 || game->turn >= game->n_players) {return ERROR;}

  strcpy(game->interface_data[game->turn]->msg, message);

  return OK;
}

const char* game_get_message(Game *game){
  if(!game || game->turn < 0 || game->turn >= game->n_players) {return NULL;}

  return game->interface_data[game->turn]->msg;
}

Status game_set_name_message(Game *game, const char* name){

  if(!game || name == NULL || game->turn < 0 || game->turn >= game->n_players) {return ERROR;}

  strcpy(game->interface_data[game->turn]->name_msg, name);

  return OK;
}

const char* game_get_name_message(Game *game){
  if(!game || game->turn < 0 || game->turn >= game->n_players) {return NULL;}

  return game->interface_data[game->turn]->name_msg;
}

Status game_command_create(Game* game){
  if (!game || game->n_players < 0 || game->n_players >= MAX_PLAYERS || game->interface_data[game->n_players] == NULL) {return ERROR;}

  game->interface_data[game->n_players]->last_cmd = command_create();

  if (game->interface_data[game->n_players]->last_cmd == NULL) {
    return ERROR;
  }

  return OK;
}

/**
 * Game turn functions implementation.
 */

int game_get_turn(Game *game){
  if (!game) {return -1;}

  return game->turn;
}

Status game_next_turn(Game *game){
  if (!game || game->n_players <= 0) {return ERROR;}

  /*works as a circular turn*/
  game->turn = (game->turn + 1) % game->n_players;

  return OK;
}

/**
 * Game print function implementation.
 */

void game_print(Game *game) {
  int i;

  printf("\n\n+--------------------------------------------------------------+\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }
  printf("\n");

  printf("=> Objects: \n");
  for (i = 0; i < game->n_objects;i++)
  {
    object_print(game->object[i]);
  }
  printf("\n");
  
  printf("=> Players: \n");
  for (i = 0; i < game->n_players; i++)
  {
    player_print(game->player[i]);
  }
  printf("\n");

  printf("=> Characters: \n");
  for (i = 0; i < game->n_characters;i++)
  {
    character_print(game->characters[i]);
  }
  printf("\n");

  printf("=> Links: \n");
  for (i = 0; i < game->n_links; i++)
  {
    link_print(game->link[i]);
  }
  printf("\n");

}