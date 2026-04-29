/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
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
#include <time.h>

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/* Option of creating a file that saves all the commands used in that game. */
void game_loop_log (Game *game, FILE *f);

static const char *game_loop_command_to_str(CommandCode code) {
  switch (code) {
    case UNKNOWN:
      return "unknown";
    case EXIT:
      return "exit";
    case MOVE:
      return "move";
    case TAKE:
      return "take";
    case DROP:
      return "drop";
    case ATTACK:
      return "attack";
    case CHAT:
      return "chat";
    case INSPECT:
      return "inspect";
    case NO_CMD:
    default:
      return "";
  }
}

static void game_loop_log_command(FILE *log_fp, Command *cmd) {
  const char *cmd_str = NULL;
  const char *arg = NULL;
  
  if (!log_fp || !cmd) {
    return;
  }

  cmd_str = game_loop_command_to_str(command_get_code(cmd));
  arg = command_get_arg(cmd, 0);

  if (arg && arg[0] != '\0') {
    fprintf(log_fp, "%s %s: %s\n", cmd_str, arg, command_to_string(command_get_return(cmd)));
  } else {
    fprintf(log_fp, "%s: %s\n", cmd_str, command_to_string(command_get_return(cmd)));
  }
}

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine;
  int result;
  Command *last_cmd = NULL;
  FILE *log_fp = NULL;
  const char *data_file = NULL;
  const char *log_file = NULL;

  if (argc != 2 && argc != 4) {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>]\n", argv[0]);
    return 1;
  }

  data_file = argv[1];
  if (argc == 4) {
    if (strcmp(argv[2], "-l") != 0) {
      fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>]\n", argv[0]);
      return 1;
    }
    log_file = argv[3];
  }
  
  result = game_loop_init(&game, &gengine, (char *)data_file);

  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  if (log_file != NULL) {
    log_fp = fopen(log_file, "w");
    if (!log_fp) {
      fprintf(stderr, "Error opening log file %s\n", log_file);
      game_loop_cleanup(game, gengine);
      return 1;
    }
  }
  /*prints game data for debugging purposes
  game_print(game); 
  */
  

  last_cmd = game_get_last_command(game);

  /*generates a seed for the random number (later should be moved to game.c)*/
  srand(time(NULL));

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
    if (log_fp) {
      game_loop_log_command(log_fp, last_cmd);
    }

    if (command_get_code(last_cmd) == EXIT || game_get_finished(game) == TRUE) 
    {
      break;
    }
        
    if (command_get_return(last_cmd) == OK)
    {
      /*shows the player the result of their action*/
      graphic_engine_paint_game(gengine, game);
      /*time given to see the result of the player's actions*/
      sleep(1);
      /*advances the turn to the next player*/
      game_next_turn(game);
      last_cmd = game_get_last_command(game);
    }
  }

  if (log_fp) {
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