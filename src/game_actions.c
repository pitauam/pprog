/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @version 5
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

/**
   Private functions
*/

/**
 * @brief the command is unknown
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_unknown(Game *game);

/**
 * @brief it has selected exit
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_exit(Game *game);

/**
 * @brief moves to the next space at the south
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_next(Game *game);

/**
 * @brief goes back to the north
 * @author Profesores PPROG
 *
 * @param game pointer to game
 */
void game_actions_back(Game *game);

/**
 * @brief moves to the next space at the west
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_left(Game *game);

/**
 * @brief moves to the next space at the east
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_right(Game *game);

/**
 * @brief the player takes the object of the space
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_take(Game *game);

/**
 * @brief the player drops the object to the space
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 */
void game_actions_drop(Game *game);

/**
 * @brief lets the player attack
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_actions_attack(Game *game);

/**
 * @brief lets the player chat
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_actions_chat(Game *game);

/**
 * @brief lets the player inspect an object
 * @author Fernando Pina
 *
 * @param game pointer to game
 */
void game_actions_inspect(Game *game);

/**
 * @brief replaces the commands to move into only one command
 * @author Santiago Pita
 *
 * @param game pointer to game
 */
void game_actions_move(Game *game);

/**
 * @brief It lets the player to recruit characters
 * @author Samuel Manzorro
 * 
 * @param game a pointer to the game
 */
void game_actions_recruit(Game *game);

/**
 * @brief It lets the player to abandon the recruited characters
 * @author Samuel Manzorro
 * 
 * @param game a pointer to the game
 */
void game_actions_abandon(Game *game);

/*
 * @brief It lets the player use the object for something
 * @author Marta López
 * 
 * @param game a pointer to the game
 
void game_actions_use(Game *game);
Nota: descomentar cuando esté hecha la funcion
*/

/**
 * @brief Gets the id of the first enemy character at a given space
 * @author Santiago Pita
 *
 * @param game a pointer to the game
 * @param space_id id of the space to inspect
 * @return enemy character id, or NO_ID if there is none
 */
Id game_actions_get_enemy_character_at(Game *game, Id space_id);

/*
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case MOVE:
      game_actions_move(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;
    
    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case CHAT:
      game_actions_chat(game);
      break;
    
    case INSPECT:
      game_actions_inspect(game);
      break;
    
    case RECRUIT:
      game_actions_recruit(game);
      break;

    case ABANDON:
      game_actions_abandon(game);
      break;

      /*
    case USE:
      game_actions_use(game);
      break;
      Nota: descomentar cuando esté hecha la funcion
*/

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_move(Game *game){
  Id future_id = NO_ID; /*Where I go*/
  Id space_id = NO_ID;  /*Where I am*/
  Bool open = FALSE;
  Direction dir = NO_DIR;
  char direction[MAX_ARG];

  Character* chr=NULL;
  Id current_char_id = NO_ID, current_char_location = NO_ID, current_char_following = NO_ID;
  int i;
  Space* actual_space = NULL, *future_space = NULL;

  strcpy(direction, command_get_arg(game_get_last_command(game)));

  if (strcmp(direction, "b") == 0 || strcmp(direction, "back") == 0)
  {
    dir = 0;
  }
  else if (strcmp(direction, "n") == 0 || strcmp(direction, "next") == 0)
  {
    dir = 1;
  }
  else if (strcmp(direction, "r") == 0 || strcmp(direction, "right") == 0)
  {
    dir = 2;
  }
  else if (strcmp(direction, "l") == 0 || strcmp(direction, "left") == 0)
  {
    dir = 3;
  }
  else {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  space_id = game_get_player_location(game);
  actual_space = game_get_space(game, space_id);
  if (NO_ID == space_id || !actual_space) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  future_id = game_get_connection(game, space_id, dir);
  future_space = game_get_space(game, future_id);
  if (NO_ID == space_id || !future_space) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  open = game_connection_is_open(game, space_id, dir);

  if (future_id != NO_ID && open == TRUE) {

    game_set_player_location(game, future_id);
    
    /*The reclutas will go with this player to the future_id space -> condiciones: MISMO ESPACIO, AMIGO, QUE ME SIGA (id de recluta == id jugador) y que esté VIVO*/

    /*Finds the character to move*/
    for (i = 0 ; i < game_get_number_of_characters(game); i++)
    {
      /*Passes through all the characters of the game*/
      current_char_id = game_get_character_id_at(game, i);
      chr = game_get_character(game, current_char_id);
      current_char_location = game_get_character_location(game, current_char_id);
      current_char_following = character_get_following(chr);

      if (current_char_id == NO_ID || !chr){
        command_set_return(game_get_last_command(game), ERROR);
        return;
      }

      if (current_char_location == space_id && character_get_friendly(chr)==TRUE && current_char_following == player_get_id(game_get_player(game)) && character_get_health(chr) > 0 && current_char_location != NO_ID) { /*CUMPLE CONDICIONES*/
        /*2. Remove character from the space_id   and   3. Add character to the future_id*/
        
        if (space_remove_character(actual_space, current_char_id) == ERROR)
        {
          command_set_return(game_get_last_command(game), ERROR);
          return;
        }

        if (space_add_character(future_space, current_char_id) == ERROR)
        {
          command_set_return(game_get_last_command(game), ERROR);
          return;
        }
        command_set_return(game_get_last_command(game), OK);
      }
    }
  }
  else
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  command_set_return(game_get_last_command(game), OK);
  return;
}


void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id object_location = NO_ID;
  Id object_id = NO_ID;
  int i;
  char object_name[MAX_ARG];
  Player *player;

  /*gets the id of the space where the player is*/
  player_location = game_get_player_location(game);
  if(player_location == NO_ID) {{
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }}

  player = game_get_player(game);


  /*saves the last command argument*/
  strcpy(object_name, command_get_arg(game_get_last_command(game)));

  if (player_inventory_full(player) == TRUE) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  for (i = 0; i < game_get_number_of_objects(game) ; i++)
  {
    /*gets the object id*/
    object_id = game_get_object_id(game, i);

    /*if the name in the argument is the same as the name of one of the objects, then it exists*/

    if (strcmp((game_get_object_name(game, game_get_object(game, object_id))), object_name) == 0)
    {
      object_location = game_get_object_location(game, object_id);
      /*if the object is in the same place as the player, then it can take it*/
      if (object_location != NO_ID && object_location == player_location)
      {
        /*sets the object to the player*/
        player_add_object(player, object_id);

        /*deletes the object from the space*/
        space_remove_object(game_get_space(game, player_location), object_id);
        command_set_return(game_get_last_command(game), OK);
        return;
      }
    }
  }


  command_set_return(game_get_last_command(game), ERROR);
  return;
}

void game_actions_drop(Game *game){
  Id space_id = NO_ID;
  Id object_id = NO_ID;
  Player* player;
  char object_name[MAX_ARG];
  Id buffer = NO_ID;
  int i;
  Bool object_exists = FALSE;

  /*gets the id of the space where the player is*/
  space_id = game_get_player_location(game);
  if(space_id == NO_ID){
    {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }
  }
  /*checks if the player has an object*/
  player = game_get_player(game);

  strcpy(object_name, command_get_arg(game_get_last_command(game)));

  for (i = 0; i < game_get_number_of_objects(game); i++)
  {
    /*gets the object id*/
    buffer = game_get_object_id(game, i);

    /*if the name in the argument is the same as the name of one of the objects, then it exists*/

    if (strcmp((game_get_object_name(game, game_get_object(game, buffer))), object_name) == 0)
    {
      object_exists = TRUE;
      object_id = buffer;
      break;
    }
    
  }

  if (object_exists == FALSE)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  if (player_find_object(player, object_id) == ERROR)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }else
  {
      /*removes the object from the player*/
    player_remove_object(player, object_id);
    /*adds the object to the space*/
    space_add_object(game_get_space(game, space_id), object_id);
  }
  
  
  

  command_set_return(game_get_last_command(game), OK);
  return;
}

void game_actions_attack(Game *game){
  Id player_location; 
  Id enemy_character_at_player_location;
  Id follower_ids[MAX_CHARACTERS];
  Id current_char_id;
  Character *enemy = NULL; 
  Character *char_aux = NULL;
  Character *current_char = NULL;
  Player *player = NULL;

  int enemy_health;
  int player_health;
  int random_number;
  int i;
  
  int random_character; /*chooses a number betwen -1 and n_following_characters to decide who gets the damage*/
  int n_followers;

  if (!game) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /*gets the id of the space where the player is located*/
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /*gets the id of the enemy character located at the same space as the player*/
  enemy_character_at_player_location = game_actions_get_enemy_character_at(game, player_location);
  if (enemy_character_at_player_location == NO_ID) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  enemy = game_get_character(game, enemy_character_at_player_location);
  if (enemy == NULL) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /*if character is friendly, return*/
  if (character_get_friendly(enemy) == TRUE) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  player = game_get_player(game);

  enemy_health = character_get_health(enemy);
  player_health = player_get_health(player);
  
  /*if character is dead or player is dead, return*/
  if (enemy_health <= 0 || player_health <= 0) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  n_followers = 0;
  for (i = 0; i < game_get_number_of_characters(game); i++)
  {
    current_char_id = game_get_character_id_at(game, i);
    current_char = game_get_character(game, current_char_id);

    if (current_char != NULL && character_get_following(current_char) == player_get_id(player) && character_get_health(current_char) > 0 && game_get_character_location(game, current_char_id) == player_location)
    {
      follower_ids[n_followers] = current_char_id;
      n_followers++;
    }
  }

  /*generates a random number between 0 and 9*/
  random_number = (rand() % 10);

  /*random number between -1 and n_followers-1*/
  random_character = ((rand() % (n_followers+1)) - 1);

  
  /*if the player wins*/
  if (random_number >= 5)
  {
    character_set_health(enemy, (enemy_health - (1 + n_followers)));
  } 
  /*if the player looses*/
  else
  {
    /*if player has no followers*/
    if (n_followers == 0)
    {
      /*player gets hit*/
      player_set_health(player, (player_health -1));
    }
    /*if it's the players turn to get hit*/
    else if (random_character == -1)
    {
      /*player gets hit*/
      player_set_health(player, (player_health -1));
    }
    /*characters following the player get hit, depending if they are followers or not*/
    else
    {
      char_aux = game_get_character(game, follower_ids[random_character]);
      character_set_health(char_aux, (character_get_health(char_aux) - 1));
    }  
  }

  /*checks if character is dead or player is dead (this should be move to another place, not inside game_actions)*/
  if (character_get_health(enemy) <= 0)
  {
    /*enemy character dies*/
    space_remove_character(game_get_space(game, player_location), enemy_character_at_player_location);
  }

  if (player_get_health(game_get_player(game)) <= 0)
  {
    /*player dies*/
    game_set_finished(game, TRUE); /*if player dies, game ends*/
  }

  if (char_aux != NULL && character_get_health(char_aux) <= 0)
  {
    /*follower character dies*/
    /*
    NOTE: this must be added when spaces can have more than one character
    space_set_character(game_get_space(game, player_location), NO_ID);  
    */
    space_remove_character(game_get_space(game, player_location), character_get_id(char_aux));
  }
  /*all above must be moved*/

  command_set_return(game_get_last_command(game), OK);
  return;
}


void game_actions_chat(Game *game){

  Id player_location = NO_ID; 
  Id character_id = NO_ID;
  Character *character = NULL;
  int i;
  char character_name[MAX_ARG];


  if (!game) {{
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }}

  /*gets the id of the space where the player is located*/
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {{
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }}

  /*Get the character wanted*/
  strcpy(character_name, command_get_arg(game_get_last_command(game))); /*name got it*/

  for (i=0 ; i < game_get_number_of_characters(game) ; i++) { /*Go through all the characters of the game comparing the name with the name of the character wanted*/
    character_id = game_get_character_id_at(game, i);
    character = game_get_character(game, character_id);
    if (strcmp(game_get_character_name(game, character), character_name) == 0) { 
      /*We found the character wanted*/

      /*if character is not friendly, return*/
      if (character_get_friendly(character) == FALSE) {{
        command_set_return(game_get_last_command(game), ERROR);
        return;
      }}

      if(game_set_message(game, character_get_message(character)) == OK){
        game_set_name_message(game, character_get_name(character));
        command_set_return(game_get_last_command(game), OK);
        return;
      }


    }
  }

  

  command_set_return(game_get_last_command(game), ERROR);
  return;
}


void game_actions_inspect(Game *game){
  Id player_location = NO_ID;
  Bool object_exists = FALSE; 
  Id Id_object_player = NO_ID;
  Object *object = NULL; 
  Player *player = NULL;
  Space *current_space = NULL;
  char object_name[MAX_ARG];
  Id buffer = NO_ID;

  int i;

  if (!game)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }
  
  /*gets the id of the space where the player is*/
  player_location = game_get_player_location(game);
  if(player_location == NO_ID) {{
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }}

  player = game_get_player(game);

  if (!player)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }
  
  current_space = game_get_space(game, player_location);

  if (!current_space)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }
  

  /*saves the last command argument*/
  strcpy(object_name, command_get_arg(game_get_last_command(game)));

  for (i = 0; i < game_get_number_of_objects(game); i++)
  {
    /*gets the object id*/
    buffer = game_get_object_id(game, i);

    /*if the name in the argument is the same as the name of one of the objects, then it exists*/

    if (strcmp((game_get_object_name(game, game_get_object(game, buffer))), object_name) == 0)
    {
      object_exists = TRUE;
      Id_object_player = buffer;
      break;
    }
    
  }

  if (object_exists == FALSE) {{
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }}
  
  if (player_inventory_empty(player) == TRUE) {{

    if (space_find_object(current_space, Id_object_player) == FALSE)
    {
      command_set_return(game_get_last_command(game), ERROR);
      return;
    }else
    {
      object = game_get_object(game, Id_object_player);
      game_set_message(game, object_get_desc(object));
      game_set_name_message(game, object_get_name(object));
      command_set_return(game_get_last_command(game), OK);
      return;
    }

  }}else
  {
    for (i = 0; i < player_get_n_objects(player); i++)
  {
    if (player_find_object(player,Id_object_player) == OK)
    {
      object = game_get_object(game, Id_object_player);
      game_set_message(game, object_get_desc(object));
      game_set_name_message(game, object_get_name(object));
      command_set_return(game_get_last_command(game), OK);
      return;
    }
    
  }
  }

    return;
}

void game_actions_recruit(Game *game) {

  int i;
  Id player_location = NO_ID, character_location = NO_ID, current_char_id = NO_ID;
  char *chr_name = NULL;
  Character *chr = NULL;

  if (!game) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
  {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  chr_name = command_get_arg(game_get_last_command(game));
  if (chr_name == NULL || chr_name[0] == '\0') {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  for (i = 0; i < game_get_number_of_characters(game); i++)
  {
    current_char_id = game_get_character_id_at(game, i);
    character_location = game_get_character_location(game, current_char_id);
    chr = game_get_character(game, current_char_id);

    if (character_location == player_location && character_get_friendly(chr) == TRUE && chr != NULL && character_get_following(chr) == NO_ID) {
      if (strcmp(chr_name, character_get_name(chr)) == 0) {
        
        character_set_following(chr, player_get_id(game_get_player(game)));
        
        command_set_return(game_get_last_command(game), OK);  /*Done successfully*/
        return;
      }
    }
  }

  command_set_return(game_get_last_command(game), ERROR);
  return;
}

void game_actions_abandon(Game *game) {
  int i;
  char *chr_name = NULL;
  Character *chr = NULL;

  if (!game) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  chr_name = command_get_arg(game_get_last_command(game));

  if (chr_name == NULL) {
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }
  
  for (i = 0; i < game_get_number_of_characters(game); i++) {
    chr = game_get_character(game, game_get_character_id_at(game, i));
    
    if (chr != NULL && character_get_following(chr) == player_get_id(game_get_player(game))) {
      if (strcmp(chr_name, character_get_name(chr)) == 0) {
        
        character_set_following(chr, NO_ID);
        command_set_return(game_get_last_command(game), OK);
        return;
      }
    }
  }

  command_set_return(game_get_last_command(game), ERROR);
  return;
}


void game_actions_use(Game *game){
  int i=0;
  Player *player = NULL;
  Object *obj = NULL;

  Id object_id = NO_ID;
  char *obj_name = NULL;

  if(game == NULL) return;

  /* Get the player */
  player = game_get_player(game);
  if(player == NULL){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /* Get object name (use "something") */
  obj_name = command_get_arg(game_get_last_command(game));
  if(obj_name == NULL){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /* Search for object */
  for(i=0; i<game_get_number_of_objects(game); i++){
    Id actual = game_get_object_id(game, i);
    Object *current_object = game_get_object(game, actual);

    if (current_object != NULL &&
        strcmp(object_get_name(current_object), obj_name) == 0) {

      object_id = actual;
      break;
    }
  }

  if(object_id == NO_ID){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  if(player_find_object(player, object_id) == ERROR){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  /* Get the object */
  obj = game_get_object(game, object_id);

  if(obj == NULL){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  if(object_get_health(obj) == 0){
    command_set_return(game_get_last_command(game), ERROR);
    return;
  }

  player_set_health(player, (player_get_health(player)+object_get_health(obj)));

  /* Remove from inventary */
  player_remove_object(player, object_id);

  command_set_return(game_get_last_command(game), OK);
}



Id game_actions_get_enemy_character_at(Game *game, Id space_id){
  int i;
  Character *chr = NULL;
  Id current_char_id = NO_ID;

  if (!game || space_id == NO_ID){
    return NO_ID;
  }

  /* searches the character list and returns the first enemy foundin that space. */
  for (i = 0; i < game_get_number_of_characters(game); i++)
  {
    current_char_id = game_get_character_id_at(game, i);
    chr = game_get_character(game, current_char_id);

    if (chr != NULL && game_get_character_location(game, current_char_id) == space_id && character_get_friendly(chr) == FALSE)
    {
      return current_char_id;
    }
  }

  return NO_ID;
}
