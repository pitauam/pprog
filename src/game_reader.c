/**
 * @brief Reads the information of the .dat
 *
 * @file game_reader.c
 * @author Santiago Pita
 * @version 2
 * @date 10-02-2025
 * @copyright GNU Public License
 */
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief loads the spaces of the game
 * @author Mario Rodriguez
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_objects(Game *game, char *filename);

/**
 * @brief loads the spaces of the game
 * @author Profesores PPROG
 *
 * @param game pointer to game
 * @param filename pointer to a tring with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief loads the links of the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param filename pointer to a string with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_links(Game *game, char *filename);

/**
 * @brief loads the characters of the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param filename pointer to a string with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_characters(Game *game, char *filename);

/**
 * @brief loads the players of the game
 * @author Santiago Pita
 *
 * @param game pointer to game
 * @param filename pointer to a string with the file name
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_players(Game *game, char *filename);

Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  Status status = OK;

  char gdesc_str[50] = ""; /* Buffer to store the graphic description */
  int i;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      gdesc_str[0] = '\0';

      toks = strtok(line + 3, "|");
      /*id of the space*/
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      for (i = 0; i < 5; i++) {
        toks = strtok(NULL, "|");
        if (toks != NULL) {
          strncat(gdesc_str, toks, 9);
        }
      }

#ifdef DEBUG
      printf("Leido: s:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        if (strlen(gdesc_str) > 0) {          /*if there is a graphic description it is inserted into the space*/
          space_set_gdesc(space, gdesc_str);
        }
        space_set_name(space, name);
        game_add_space(game, space);

      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_reader_load_objects(Game *game, char *filename){

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
#ifdef DEBUG
      printf("Leido: o:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        object_set_desc(object, message);
        game_set_object_location(game, location, id);
        game_add_object(game, object);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;

}

Game* game_reader_create_from_file(char *filename) {
  Game *game;

  game = game_create();
  if (game == NULL) {
    return NULL;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_objects(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_links(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_players(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_characters(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  /*
  if (game_get_player(game) == NULL) {
    Player *player = player_create(PLAYER_ID);

    if (player == NULL || game_set_player(game, player) == ERROR) {
      player_destroy(player);
      game_destroy(game);
      return NULL;
    }

    if (game_get_space_id_at(game, 0) != NO_ID) {
      game_set_player_location(game, game_get_space_id_at(game, 0));
    }
  }
    */

  return game;
}


Status game_reader_load_links(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;

  Id id = NO_ID;
  Id origin_id = NO_ID;
  Id destination_id = NO_ID;

  Direction dir = NO_DIR;
  Link *link;
  Status status = OK;
  int open;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {

      toks = strtok(line + 3, "|");
      /*id of the link*/
      id = atol(toks);
      /*name of the origin space*/
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      /*id of the origin space*/
      origin_id = atol(toks);
      toks = strtok(NULL, "|");
      /*id of the destination space*/
      destination_id = atol(toks);
      toks = strtok(NULL, "|");
      /*direction of the link*/
      dir = atol(toks);
      toks = strtok(NULL, "|");
      /*wheter the link is open or closed*/
      open = atol(toks);


      link = link_create(id);
      if (link != NULL) {

        link_set_origin(link, origin_id);
        link_set_destination(link, destination_id);
        link_set_direction(link, dir);
        link_set_open(link, open);
        link_set_name(link, name);
        game_add_link(game, link);
      }
    }
  }
  
  if (ferror(file)) 
  {
    status = ERROR;
  }

  fclose(file);
  return status;
}


Status game_reader_load_characters(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc_str[10] = ""; 
  char message[WORD_SIZE] = "";
  char *toks = NULL;

  Id id = NO_ID;
  Id space_id = NO_ID;
  int health_points;
  int friendly;

  Character *character = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      /*id of the character*/
      id = atol(toks);
      /*name of the character*/
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      /*graphic description of the character*/
      strcpy(gdesc_str, toks);
      toks = strtok(NULL, "|");
      /*id of the space where it will spawn*/
      space_id = atol(toks);
      toks = strtok(NULL, "|");
      /*health points*/
      health_points = atol(toks);
      toks = strtok(NULL, "|");
      /*wheter the character is friendly or not*/
      friendly = atol(toks);
      toks = strtok(NULL, "|");
      /*message the character has*/
      strcpy(message, toks);

      character = character_create(id);
      if (character != NULL) {
        character_set_name(character, name);
        character_set_description(character, gdesc_str);
        space_add_character(game_get_space(game, space_id), id);
        character_set_health(character, health_points);
        if (friendly == 1)
        {
          character_set_friendly(character, TRUE);
        }
        else
        {
          character_set_friendly(character, FALSE);
        }
        character_set_message(character, message);
        game_add_character(game, character);
      }
    }
  }
  
  if (ferror(file)) 
  {
    status = ERROR;
  }

  fclose(file);
  return status;
}


Status game_reader_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc_str[10] = "";
  char *toks = NULL;
  
  Id id = NO_ID;
  Id space_id = NO_ID;
  int health_points;
  int max_objects;
  Player *player = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      /*id of the player*/
      id = atol(toks);
      toks = strtok(NULL, "|");
      /*name of the player*/
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      /*graphic description of the player*/
      strcpy(gdesc_str, toks);
      toks = strtok(NULL, "|");
      /*id of the space where it will spawn*/
      space_id = atol(toks);
      toks = strtok(NULL, "|");
      /*health points*/
      health_points = atol(toks);
      toks = strtok(NULL, "|");
      /*maximum number of objects in the backpack*/
      max_objects = atol(toks);

      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_description(player, gdesc_str);
        player_set_location(player, space_id);
        player_set_health(player, health_points);
        player_set_max_objects(player, max_objects);

        game_command_create(game);

        game_set_player(game, player);
    
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}