/**
 * @brief Reads the information of the .dat
 *
 * @file game_reader.c
 * @author Santiago Pita
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_ID1 11
#define SPACE_ID2 12

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

Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
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
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

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
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        
        if (strlen(gdesc_str) > 0) {          /*if there is a graphic description it is inserted into the space*/
          space_set_gdesc(space, gdesc_str);
        }
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
#ifdef DEBUG
      printf("Leido: o:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
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
    return NULL;
  }

  if (game_reader_load_objects(game, filename) == ERROR) {
    return NULL;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  /*places the characters*/
  space_set_character(game_get_space(game, SPACE_ID1), CHARACTER1);
  space_set_character(game_get_space(game, SPACE_ID2), CHARACTER2);

  return game;
}