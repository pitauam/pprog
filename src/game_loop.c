/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Marta López
 * @version 0
 * @date 05-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_reader.h"
#include "game_rules.h"
#include <time.h>

#define DETERMINISTIC_SEED 1

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/* Option of creating a file that saves all the commands used in that game. */
void game_loop_log (Game *game, FILE *f);

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine;
  int result, a=0;
  Bool deterministic = FALSE;
  Command *last_cmd = NULL;
  FILE *log_fp = NULL;
  const char *data_file = NULL;
  const char *log_file = NULL;
  char name[WORD_SIZE];

  if (argc < 2 || argc > 5) {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log>] [-d]\n", argv[0]);
    return 1;
  }

  data_file = argv[1];

  for (a = 2; a < argc; a++) {
    if (strcmp(argv[a], "-l") == 0) {
      if (a + 1 >= argc || log_file != NULL) {
        fprintf(stderr, "Use: %s <game_data_file> [-l <log>] [-d]\n", argv[0]);
        return 1;
      }
      log_file = argv[a + 1];
      a++;
    } else if (strcmp(argv[a], "-d") == 0) {
      deterministic = TRUE;
    } else {
      fprintf(stderr, "Use: %s <game_data_file> [-l <log>] [-d]\n", argv[0]);
      return 1;
    }
  }
  
  result = game_loop_init(&game, &gengine, (char *)data_file);

  for(a =0; a < game_get_number_of_players(game); a++){
    printf("Name of player %d (NO spaces): ", a+1);
    while(scanf("%s", name) != 1){
      printf("\nERROR, name not valid.");
      printf("Name of player %d (NO spaces): ", a+1);
    }

    player_set_name(game_get_player(game), name);
    game_next_turn(game);
  }

   if (log_file != NULL) {
    log_fp = fopen(log_file, "w");
    game_loop_log(game, log_fp);
    if (!log_fp) {
      fprintf(stderr, "Error opening log file %s\n", log_file);
      game_loop_cleanup(game, gengine);
      return 1;
    }
  }

  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
  if (log_fp != NULL)
  {
    fclose(log_fp);
  }
    game_destroy(game);
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
  if (log_fp != NULL)
  {
    fclose(log_fp);
  }
    return 1;
  }

  if (game_get_number_of_players(game) <= 0)
  {
    fprintf(stderr, "Error: game data file has no players.\n");
    game_loop_cleanup(game, gengine);
    return 1;
  }

  last_cmd = game_get_last_command(game);

  /*generates a seed for the random number*/
  if (deterministic == TRUE) {
    srand(DETERMINISTIC_SEED);
  } else {
    srand(time(NULL));
  }

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game, FALSE);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
    
    if (log_fp) {
      game_loop_log(game, log_fp);
    }

    if (command_get_code(last_cmd) == EXIT || game_get_finished(game) == TRUE) 
    {
      game_rules_update(game);
      break;
    }
        
    if (command_get_return(last_cmd) == OK)
    {
      /*shows the player the result of their action*/
      graphic_engine_paint_game(gengine, game, TRUE);
      /*updates the game rules*/
      game_rules_update(game);
      /*time given to see the result of the player's actions*/
      sleep(1);
      /*advances the turn to the next player*/
      game_next_turn(game);
      last_cmd = game_get_last_command(game);
    }
  }

  if (log_fp != NULL) {
    fclose(log_fp);
  }
  game_loop_cleanup(game, gengine);
  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  
  *game = game_reader_create_from_file(file_name);
  if (*game == NULL) {
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    game_destroy(*game);
    return 1;
  }

  return 0;
}

void game_loop_cleanup(Game* game, Graphic_engine *gengine) {
  graphic_engine_destroy(gengine);
  game_destroy(game);
}

void game_loop_log (Game *game, FILE *f) {
  CommandCode last_cmd = UNKNOWN;
  Status last_command_status = ERROR;
  char line[WORD_SIZE];
  char *str = NULL;
  char last_cmd_arg[CMD_LENGTH];
  char *arg = NULL;

  if(!game || !f)
  {
    return;
  }

  last_cmd = command_get_code(game_get_last_command(game));
  last_command_status = command_get_return(game_get_last_command(game));

  last_cmd_arg[0] = '\0';
  arg = command_get_arg(game_get_last_command(game), 0);

  if (arg != NULL && arg[0] != '\0')
  {
    strncpy(last_cmd_arg, arg, CMD_LENGTH-1); /* We need strncpy because we want to define the size. */
    last_cmd_arg[CMD_LENGTH-1] = '\0';
  }

  str = command_to_string(last_cmd); /* We need this new function because we need to change the command to string. */
  
  if (last_cmd_arg[0] == '\0')
  {
    if (last_command_status == OK)
    {
      sprintf(line, "%s: OK\n", str);
    } else {
      sprintf(line, "%s: ERROR\n", str);
    }
  } else
  {
    if (last_command_status == OK)
    {
      sprintf(line, "%s %s: OK\n", str, last_cmd_arg);
    } else {
      sprintf(line, "%s %s: ERROR\n", str, last_cmd_arg);
    }
  }

  fprintf(f, "Player %d's turn:\n", game_get_turn(game)+1);
  fprintf(f, "%s\n", line);
}