/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 4
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 90  /*!< Width of the map area */
#define WIDTH_DES 37  /*!< Width of the description area */
#define WIDTH_BAN 25  /*!< Width of the banner area */
#define HEIGHT_MAP 32 /*!< Height of the map area */
#define HEIGHT_BAN 1  /*!< Height of the banner area */
#define HEIGHT_HLP 2  /*!< Height of the help area */
#define HEIGHT_FDB 3  /*!< Height of the feedback area */
#define ROOM_HEIGHT 8

/**
 * @brief Graphic engine
 *
 * This struct stores all the information related to the graphic engine.
 */
struct _Graphic_engine {
  Area *map;      /*!< Pointer to the map area */
  Area *descript; /*!< Pointer to the description area */
  Area *banner;   /*!< Pointer to the banner area */
  Area *help;     /*!< Pointer to the help area */
  Area *feedback; /*!< Pointer to the feedback area */
};

/*definition of private functions*/


/**
 * @brief prints a link and its destination space in the description area
 * @author Iker Diaz
 *
 * @param ge pointer to the graphic engine
 * @param game pointer to the game
 * @param origin_id id of the current space
 * @param direction direction of the link
 * @param direction_name string with the name of the direction
 */
void graphic_engine_print_link_info(Graphic_engine *ge, Game *game, Id origin_id, Direction direction, const char *direction_name);


/*defines place-place*/


Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_box(Game *game, char box[10][WORD_SIZE * 3], char *characters, Space *space, char *objects, char *player, Id space_id) {

  int n, j;
  char str[WORD_SIZE] = {'\0'};

  if (!game)
  {
    return;
  }
  
  if (space_id != NO_ID)
  {
    sprintf(str, "+------------------+");
    strcat(box[0], str);
  
    if (space_id == game_get_player_location(game))
    {
      sprintf(str, "| %-3.3s        %3d   |", player, (int)space_id);
      strcat(box[1], str);
    } else {
      sprintf(str, "|            %3d   |", (int)space_id);
      strcat(box[1], str);
    }

    sprintf(str, "|    %-8.8s      |", characters);
    strcat(box[2], str);

    for (n = 0; n < GDESC_SIZE1; n++)
    {
      if (space_get_gdesc_line(space, n) != NULL)
      {
        if (space_is_discovered(space))
        {
          sprintf(str, "|   %-9.9s      |", space_get_gdesc_line(space, n));
          strcat(box[n+3], str);

        } else {
          sprintf(str, "|                  |");
          strcat(box[n+3], str);
        }
      }
    }

    sprintf(str, "|%-15.15s   |", objects);
    strcat(box[8], str);

    sprintf(str, "+------------------+");
    strcat(box[9], str);
  } else {
    for (j = 0; j < GDESC_SIZE2; j++)
    {
      sprintf(str, "                    ");
      strcat(box[j], str);
    }
  }
}

void graphic_engine_paint_box_space_vertical(Game *game, char box[10][WORD_SIZE * 3], Id space_id, Direction direction) {

  int j;

  char str[WORD_SIZE] = {'\0'};

  for (j = 0; j < GDESC_SIZE2; j++)
  {
    if (j == 7 && space_id != NO_ID)
    {
      if (direction == W)
      {
        sprintf(str, " <");
        strcat(box[j], str);
      } else if (direction == E) {
        sprintf(str, "> ");
        strcat(box[j], str);
      }
    } else {
      sprintf(str, "  ");
      strcat(box[j], str);
    }
  }
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID, obj_loc = NO_ID, obj_id = NO_ID, character_id = NO_ID, player_obj_id = NO_ID, char_loc = NO_ID;
  char obj_act[WORD_SIZE] = {'\0'};
  char obj_back[WORD_SIZE] = {'\0'};
  char obj_next[WORD_SIZE] = {'\0'};
  char obj_left[WORD_SIZE] = {'\0'};
  char obj_right[WORD_SIZE] = {'\0'};
  char chr_act[WORD_SIZE] = {'\0'};
  char chr_back[WORD_SIZE] = {'\0'};
  char chr_next[WORD_SIZE] = {'\0'};
  char chr_left[WORD_SIZE] = {'\0'};
  char chr_right[WORD_SIZE] = {'\0'};
  char player_act[WORD_SIZE] = {'\0'};
  char box_up[10][WORD_SIZE * 3] = {{'\0'}};
  char box_act[10][WORD_SIZE * 3] = {{'\0'}};
  char box_down[10][WORD_SIZE * 3] = {{'\0'}};
  /*char msg[WORD_SIZE] = {'\0'};
  char chr_msg[WORD_SIZE] = {'\0'};*/

  char str[WORD_SIZE * 10];
  CommandCode last_cmd = UNKNOWN;
  /*Status last_command_status = OK;*/
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, j, k;
  Object *obj = NULL;
  Character *chr = NULL;
  Player *player = NULL;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    id_back = game_get_connection(game, id_act, N);
    id_next = game_get_connection(game, id_act, S);
    id_left = game_get_connection(game, id_act, W);
    id_right = game_get_connection(game, id_act, E);

    for (i=0; i < game_get_number_of_objects(game); i++)
    {
      obj_id = game_get_object_id_at(game, i);
      obj = game_get_object(game, obj_id);

      if (obj != NULL)
      {
        if (game_get_object_location(game, obj_id) == NO_ID)
        {
          continue;

        } else if (game_get_object_location(game, obj_id) == id_act)
        {
          strncat(obj_act, object_get_name(obj), strlen(object_get_name(obj)));
          strncat(obj_act, " ", WORD_SIZE - strlen(obj_act) - 1);

        } else if (game_get_object_location(game, obj_id) == id_back)
        {
          strncat(obj_back, object_get_name(obj), strlen(object_get_name(obj)));
          strncat(obj_back, " ", WORD_SIZE - strlen(obj_back) - 1);

        } else if (game_get_object_location(game, obj_id) == id_next)
        {
          strncat(obj_next, object_get_name(obj), strlen(object_get_name(obj)));
          strncat(obj_next, " ", WORD_SIZE - strlen(obj_next) - 1);

        } else if (game_get_object_location(game, obj_id) == id_left)
        {
          strncat(obj_left, object_get_name(obj), strlen(object_get_name(obj)));
          strncat(obj_left, " ", WORD_SIZE - strlen(obj_left) - 1);

        } else if (game_get_object_location(game, obj_id) == id_right)
        {
          strncat(obj_right, object_get_name(obj), strlen(object_get_name(obj)));
          strncat(obj_right, " ", WORD_SIZE - strlen(obj_right) - 1);
        }
      }
    }

    for (k = 0; k < game_get_number_of_characters(game); k++)
    {
      character_id = game_get_character_id_at(game, k);
      chr = game_get_character(game, character_id);

      if (chr != NULL && character_get_health(chr) > 0)
      {
        if (game_get_character_location(game, character_id) == id_act)
        {
          strncat(chr_act, character_get_description(chr), strlen(character_get_description(chr)));
          strncat(chr_act, " ", WORD_SIZE - strlen(chr_act) - 1);

        } else if (game_get_character_location(game, character_id) == id_back)
        {
          strncat(chr_back, character_get_description(chr), strlen(character_get_description(chr)));
          strncat(chr_back, " ", WORD_SIZE - strlen(chr_back) - 1);

        } else if (game_get_character_location(game, character_id) == id_next)
        {
          strncat(chr_next, character_get_description(chr), strlen(character_get_description(chr)));
          strncat(chr_next, " ", WORD_SIZE - strlen(obj_next) - 1);

        } else if (game_get_character_location(game, character_id) == id_left)
        {
          strncat(chr_left, character_get_description(chr), strlen(character_get_description(chr)));
          strncat(chr_left, " ", WORD_SIZE - strlen(chr_left) - 1);

        } else if (game_get_character_location(game, character_id) == id_right)
        {
          strncat(chr_right, character_get_description(chr), strlen(character_get_description(chr)));
          strncat(chr_right, " ", WORD_SIZE - strlen(chr_right) - 1);
        }
      }
    }

    strncat(player_act, player_get_description(game_get_player(game)), strlen(player_get_description(game_get_player(game))));
    strncat(player_act, " ", WORD_SIZE - strlen(player_act) - 1);

    graphic_engine_paint_box(game, box_up, NULL, NULL, "", NULL, NO_ID);
    if (id_back != NO_ID)
    {
      graphic_engine_paint_box_space_vertical(game, box_up, id_left, W);
      graphic_engine_paint_box(game, box_up, chr_back, game_get_space(game, id_back), obj_back, NULL, id_back);
      graphic_engine_paint_box_space_vertical(game, box_up, id_right, E);
    } else {
      graphic_engine_paint_box_space_vertical(game, box_up, NO_ID, W);
      graphic_engine_paint_box(game, box_up, chr_back, game_get_space(game, id_back), obj_back, NULL, NO_ID);
      graphic_engine_paint_box_space_vertical(game, box_up, NO_ID, E);
    }

    graphic_engine_paint_box(game, box_up, NULL, NULL, "", NULL, NO_ID);

    for (i = 0; i < 10; i++)
    {
      screen_area_puts(ge->map, box_up[i]);
    }

    if (id_back != NO_ID)
    {
      sprintf(str, "                           ^                         ");
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "                                                     ");
      screen_area_puts(ge->map, str);
    }
    

    graphic_engine_paint_box(game, box_act, chr_left, game_get_space(game, id_left), obj_left, NULL, id_left);    
    graphic_engine_paint_box_space_vertical(game, box_act, id_left, W);
    graphic_engine_paint_box(game, box_act, chr_act, game_get_space(game, id_act), obj_act, player_act, id_act);
    graphic_engine_paint_box_space_vertical(game, box_act, id_right, E);
    graphic_engine_paint_box(game, box_act, chr_right, game_get_space(game, id_right), obj_right, NULL, id_right);

    for (i = 0; i < 10; i++)
    {
      screen_area_puts(ge->map, box_act[i]);
    }

    if (id_next != NO_ID)
    {
      sprintf(str, "                           V                         ");
    screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "                                                     ");
      screen_area_puts(ge->map, str);
    }
    

    graphic_engine_paint_box(game, box_down, NULL, NULL, "", NULL, NO_ID);
    if (id_next != NO_ID)
    {
      graphic_engine_paint_box_space_vertical(game, box_down, id_left, W);
      graphic_engine_paint_box(game, box_down, chr_next, game_get_space(game, id_next), obj_next, NULL, id_next);
      graphic_engine_paint_box_space_vertical(game, box_down, id_right, E);
    } else {
      graphic_engine_paint_box_space_vertical(game, box_down, NO_ID, W);
      graphic_engine_paint_box(game, box_down, chr_next, game_get_space(game, id_next), obj_next, NULL, NO_ID);
      graphic_engine_paint_box_space_vertical(game, box_down, NO_ID, E);
    }
    graphic_engine_paint_box(game, box_down, NULL, NULL, "", NULL, NO_ID);

    for (i = 0; i < 10; i++)
    {
      screen_area_puts(ge->map, box_down[i]);
    }
  }


  player = game_get_player(game);
  
  /* Paint in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, " TURN: %i", game_get_turn(game)+1);
  screen_area_puts(ge->descript, str);
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, " Player name: %s (%s)",player_get_name(player), player_get_description(player));
  screen_area_puts(ge->descript, str);
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " Health : %d", player_get_health(player));
  screen_area_puts(ge->descript, str);
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  if(player_inventory_empty(player) == FALSE){
  sprintf(str," Player carries: ");
  screen_area_puts(ge->descript, str);
    for(i=0; i < player_get_n_objects(player); i++){
      player_obj_id = player_get_object_id(player, i);
      if (player_obj_id != NO_ID) {
        sprintf(str, " %12s (%ld)", object_get_name(game_get_object(game, player_obj_id)), player_obj_id);
        screen_area_puts(ge->descript, str);
      } 
    }
    
  }
  else 
  {
    sprintf(str, " Inventory is empty.");
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " Objects :");
  screen_area_puts(ge->descript, str);
  for(i = 0; i < game_get_number_of_objects(game); i++){
    if ((obj_loc = game_get_object_location(game, game_get_object_id_at(game, i) )) != NO_ID) {
    
    sprintf(str, "    %5s:% 3d", (game_get_object_name(game, game_get_object(game, game_get_object_id_at(game, i)))), (int)obj_loc);
    
    screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, " Characters :");
  screen_area_puts(ge->descript, str);
  
  for(i=0; i < game_get_number_of_spaces(game); i++){
    /*char_id = game_get_character_location(game, game_get_character_id(game, game_get_space_id_at(game, i)));*/


    char_loc = game_get_space_id_at(game, i);

    /*for every character in the space*/
    for (j = 0; j < space_get_n_characters(game_get_space(game, char_loc)); j++)
    {
      character_id = space_get_character_id_at(game_get_space(game, char_loc), j);
    
      if (character_id != NO_ID) 
      {
        char_loc = game_get_space_id_at(game,i);

        chr = game_get_character(game, character_id);

        sprintf(str, "%9s (%3s):% 3d (%i)", (character_get_name(chr)),character_get_description(chr), (int)char_loc, character_get_health(chr));
    
        screen_area_puts(ge->descript, str);
      }

    }
    
  }

  player = game_get_player(game);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " Links :");
  screen_area_puts(ge->descript, str);
  graphic_engine_print_link_info(ge, game, id_act, N, "North");
  graphic_engine_print_link_info(ge, game, id_act, S, "South");
  graphic_engine_print_link_info(ge, game, id_act, E, "East");
  graphic_engine_print_link_info(ge, game, id_act, W, "West");
  graphic_engine_print_link_info(ge, game, id_act, U, "Up");
  graphic_engine_print_link_info(ge, game, id_act, D, "Down");
  
/*funcion original*/
/*
  if (player_inventory_empty(player) == FALSE)
  {

    if (player_object == 23) if the object is a rose (easter egg)
    {
      sprintf(str, " Player has a %s <3", object_get_name(game_get_object(game, player_get_object(player))));
    }
    else sprintf(str, " Player has '%s'", object_get_name(game_get_object(game, player_get_object(player))));
    }
  
    }
  else
  {
    sprintf(str, " Player has no objects");
  }
*/
  
  /*prints the message of a character*/

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, " Message from %s: %s",game_get_name_message(game), game_get_message(game));
  screen_area_puts(ge->descript, str);

  game_set_message(game, "\0"); /*removes the message*/
  game_set_name_message(game, "\0"); /*removes the name*/
  
  
  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     move or m (right,left,back,next,up,down), attack or a, chat or c, take or t, drop or d, inspect or i, use or u, recruit or r, open or o, exit or e");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  if(command_get_return(game_get_last_command(game))){
    sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL],cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }else {
    sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL],cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  screen_area_puts(ge->feedback, str);
  

  /* Dump to the terminal */
  screen_paint((game_get_turn(game)+5)%MAX_PLAYERS);
  printf("prompt-> ");

}


/**
 * @brief prints a link and its destination space
 * @author Iker Diaz
 *
 * @param ge pointer to the graphic engine
 * @param game pointer to the game
 * @param origin_id id of the current space
 * @param direction direction of the link
 * @param direction_name string with the name of the direction
 */
void graphic_engine_print_link_info(Graphic_engine *ge, Game *game, Id origin_id, Direction direction, const char *direction_name){
  Id destination_id = NO_ID;
  Space *destination_space = NULL;
  char str[255];

  if (!ge || !game || origin_id == NO_ID || !direction_name) {
    return;
  }

  destination_id = game_get_connection(game, origin_id, direction);
  if (destination_id == NO_ID) {
    return;
  }

  destination_space = game_get_space(game, destination_id);
  if (!destination_space) {
    return;
  }

  sprintf(str, "    %s -> %3ld %.16s", direction_name, (long)destination_id, space_get_name(destination_space));
  screen_area_puts(ge->descript, str);
}