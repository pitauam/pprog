/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 3
 * @date 10-03-2026
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

#define WIDTH_MAP 90
#define WIDTH_DES 29
#define WIDTH_BAN 25
#define HEIGHT_MAP 27
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

#define ROOM_HEIGHT 8 - 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};
/*definition of private functions*/
void graphic_engine_space_place(Graphic_engine *ge,Game *game, Id id_act);

void graphic_engine_2place(Graphic_engine *ge,Game *game, Id id_left, Id id_act);

void graphic_engine_space_2place(Graphic_engine *ge,Game *game, Id id_act, Id id_right);

void graphic_engine_3place(Graphic_engine *ge,Game *game, Id id_left, Id id_act, Id id_right);


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

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right = NO_ID, id_left = NO_ID, obj_loc = NO_ID, char_loc = NO_ID;
  Space *space_act = NULL;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int n_objects;
  int n_characters;
  int i = 0; 

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_right = space_get_east(space_act);
    id_left = space_get_west(space_act);

    n_objects = game_get_number_of_objects(game);
    n_characters = game_get_number_of_characters(game);

    /*imprime el anterior*/
    if (id_back != NO_ID) {
      graphic_engine_space_place(ge, game, id_back);
    }
    /*Imprime el actual*/
    if (id_act != NO_ID) {
      
      if(id_left != NO_ID && id_right != NO_ID){
        graphic_engine_3place(ge, game, id_left, id_act, id_right);
        i++;
      }
      if(id_left != NO_ID){
        if(id_right== NO_ID){
          graphic_engine_2place(ge, game, id_left, id_act);
          i++;
        }
      }
      if(id_right != NO_ID){
        if(id_left== NO_ID){
          graphic_engine_space_2place(ge, game, id_act, id_right);
          i++;
        }
      }
      if(i == 0){
        graphic_engine_space_place(ge, game, id_act);
      }
      }
      

    /*^C>*/

/*Imprime la siguiente*/
    if (id_next != NO_ID) {
      graphic_engine_space_place(ge, game, id_next);
    }


  /* Paint in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "Objects:");
  screen_area_puts(ge->descript, str);
  for(i=0; i < n_objects; i++){
    if ((char_loc = game_get_character_id(game, game_get_space_id_at(game, i) )) != NO_ID) {
    
    sprintf(str, "%9s:% 3d", (game_get_object_name(game, game_get_object(game, game_get_object_id(game, i)))), (int)obj_loc);
    
    screen_area_puts(ge->descript, str);
    }
  }
  sprintf(str,"\n");
  screen_area_puts(ge->descript, str);


  for(i=0; i < n_characters; i++){
    if ((obj_loc = game_get_object_location(game, game_get_object_id(game, i) )) != NO_ID) {
    
    sprintf(str, "%9s:% 3d", (game_get_object_name(game, game_get_object(game, game_get_object_id(game, i)))), (int)obj_loc);
    
    screen_area_puts(ge->descript, str);
    }
  }
  
  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, attack or a, chat or c, take or t, drop or d, exit or e,");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
  }
}

/*prints -x-*/
void graphic_engine_space_place(Graphic_engine *ge,Game *game, Id id_act){
  char str[255];
  char obj[MAX_CHARACTERS];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len;

  if (ge == NULL) {return;}
  if (id_act == NO_ID){return;}
  
  player_location = game_get_player_location(game);
  n_objects = game_get_number_of_objects(game);
  /*divididos por 3*/
  sprintf(str, "                       +------------------+");
  screen_area_puts(ge->map, str);
  /*checks if the player is in this space*/
  if (player_location == id_act) 
  {
    sprintf(str, "                       | :D%15d|", (int)id_act);
  } 
  else 
  {
    sprintf(str, "                       |%18d|", (int)id_act);
  }
  
  screen_area_puts(ge->map, str);
  sprintf(str, "                       |                  |");

  /*height's -2 is because of the 2 minimum screen_area_puts above*/
  for (j = 0; j < ROOM_HEIGHT; j++)
  {
    screen_area_puts(ge->map, str);
  }
  strcpy(str, "                       |          ");

  len = 0;
  /*prints first place objects*/
  for(i=0; i < n_objects; i++){
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_act)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj);
      strcat(str, " "); 
      len+= strlen(obj) + 1;
    }
  }
  
  for (j = 0; j < 8 - len; j++) {
    strcat(str, " ");
  }
  strcat(str, "|");

  screen_area_puts(ge->map, str);
  sprintf(str, "                       +------------------+");
  screen_area_puts(ge->map, str);

}
/*prints xx-*/
void graphic_engine_2place(Graphic_engine *ge,Game *game, Id id_left, Id id_act){
  char str[255];
  char obj[MAX_CHARACTERS];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len1;
  int len2;
  player_location = game_get_player_location(game);
  n_objects = game_get_number_of_objects(game);

  sprintf(str, "+------------------+   +------------------+");
  screen_area_puts(ge->map, str);
  /*checks if the player is in this space*/
  if (player_location == id_act) 
  {
    sprintf(str, "|%18d|   | :D%15d|", (int)id_left, (int)id_act);  } 
  else 
  {
    sprintf(str, "|%18d|   |%18d|", (int)id_left, (int)id_act);
  }
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  |   |                  |");

  /*height's -2 is because of the 2 minimum screen_area_puts above*/
  for (j = 0; j < ROOM_HEIGHT; j++)
  {
    screen_area_puts(ge->map, str);
  }
  
  /*prints first place objects*/
  strcpy(str, "|             "); 
  len1 = 0;
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_left)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      len1 += strlen(obj) + 1;
    }
  }

  strcat(str, "     |   ");
  /*prints second place objects*/
  strcat(str, "|             "); 
  len2 = 0;
  for(i=0; i < n_objects; i++)
  {
  if (game_get_object_location(game, game_get_object_id(game, i)) == id_act)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      len2 += strlen(obj)+1;   
    }
  }
  
  if (len1 <= 0)
  {
    strcat(str, "     |"); 
    screen_area_puts(ge->map, str);
  }
  else
  {
    for (j = 0; j < 8 - len2; j++)
    { 
      strcat(str, " ");
    }

  strcat(str, "|"); 

  screen_area_puts(ge->map, str);
  }

  sprintf(str, "+------------------+   +------------------+");
  screen_area_puts(ge->map, str);
  
}
/*prints xxx*/
void graphic_engine_3place(Graphic_engine *ge,Game *game, Id id_left, Id id_act, Id id_right){
  char str[255];
  char obj[MAX_CHARACTERS];
  Id player_location;
  int n_objects;
  int i;
  int j;


  player_location = game_get_player_location(game);
  n_objects = game_get_number_of_objects(game);

  sprintf(str, "  |%18d| | :D%15d| |%18d|", (int)id_left, (int)id_act, (int)id_right);

  sprintf(str, "+------------------+   +------------------+   +------------------+");
  screen_area_puts(ge->map, str);
  /*checks if the player is in this space*/
  if(player_location == id_act){
    sprintf(str, "|%18d|   | :D%15d|   |%18d|", (int)id_left, (int)id_act, (int)id_right);
  }else{
    sprintf(str, "|%18d|   |%15d|   |%18d|", (int)id_left, (int)id_act, (int)id_right);
  }
  screen_area_puts(ge->map, str);
  sprintf(str, "|                |   |                |   |                |");

  for (j = 0; j < ROOM_HEIGHT; j++) {
    screen_area_puts(ge->map, "|                  |   |                  |   |                  |");
  }

  /*prints first place objects*/
  strcpy(str, "|             "); 
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_left)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      strcat(str, " "); 

    }
    else
    {
      strcat(str, " "); 
    }
  }
  strcat(str, " |   ");
  /*prints second place objects*/
  strcat(str, "|          "); 
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_act)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      strcat(str, " "); 

    }
    else
    {
      strcat(str, " "); 
    }
  }
  strcat(str, "    |   ");
  /*prints third place*/
  strcat(str, "|          "); 
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_right)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      strcat(str, " "); 

    }
    else
    {
      strcat(str, " "); 
    }
  }
  strcat(str, "    |");
  screen_area_puts(ge->map, str);
  sprintf(str, "+------------------+   +------------------+   +------------------+");
  screen_area_puts(ge->map, str);

}
/*prints -xx*/
void graphic_engine_space_2place(Graphic_engine *ge,Game *game, Id id_act, Id id_right){
  char str[255];
  char obj[MAX_CHARACTERS];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len1;
  int len2;

  player_location = game_get_player_location(game);
  n_objects = game_get_number_of_objects(game);

  sprintf(str, "                       +------------------+   +------------------+");
  screen_area_puts(ge->map, str);
  /*checks if the player is in this space*/
  if(player_location == id_act){
    sprintf(str, "                       | :D%15d|   |%18d|", (int)id_act, (int)id_right);
  }else{
    sprintf(str, "                     |%15d|   |%18d|", (int)id_act, (int)id_right);
  }
  screen_area_puts(ge->map, str);
  sprintf(str, "                       |                  |   |                  |");
  for (j = 0; j < ROOM_HEIGHT; j++)
  {
    screen_area_puts(ge->map, str);
  }
  strcpy(str, "                       ");
  len1 = 0;
  /*prints first place objects*/
  strcat(str, "|            "); 
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_act)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      strcat(str, " ");
      len1 += strlen(obj) + 1;
    }
  }
  strcat(str, "      |   ");
  /*prints second place objects*/
  strcat(str, "|            "); 
  len2 = 0;
  for(i=0; i < n_objects; i++)
  {
    if (game_get_object_location(game, game_get_object_id(game, i)) == id_right)
    {
      strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
      strcat(str, obj); 
      strcat(str, " ");
      len2 += strlen(obj) + 1;
    }
  }
  strcat(str, "      |");
  screen_area_puts(ge->map, str);
  sprintf(str, "                       +------------------+   +------------------+");
  screen_area_puts(ge->map, str);

}
/*original

 Paint the in the map area 
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_right = space_get_east(space_act);
    id_left = space_get_west(space_act);

    n_objects = game_get_number_of_objects(game);

    imprime el anterior*
    if (id_back != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d |", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |           |");
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      strcpy(str, "  |     "); 
      for(i=0; i < n_objects; i++){
          if (game_get_object_location(game, game_get_object_id(game, i)) == id_back){
            strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
            strcat(str, obj); 
          }else{
            strcat(str, " "); 
          }
      }
      strcat(str, "     |"); 
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
    }
    Imprime el actual
    if (id_act != NO_ID) {
      
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | :D      %2d |", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |           |");
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      strcpy(str, "  |     "); 
      for(i=0; i < n_objects; i++){
          if (game_get_object_location(game, game_get_object_id(game, i)) == id_act){
              strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
              strcat(str, obj); 
          }else{
              strcat(str, " "); 
          }
      }
      strcat(str, "     |"); 
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    ^C>

  Imprime la siguiente*
    if (id_next != NO_ID) {
      
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d |", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |           |");
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      screen_area_puts(ge->map, str);
      strcpy(str, "  |     "); 
      for(i=0; i < n_objects; i++){
          if (game_get_object_location(game, game_get_object_id(game, i)) == id_next){
            strcpy(obj, game_get_object_name(game, game_get_object(game, game_get_object_id(game, i))));
            strcat(str, obj); 
          }else{
            strcat(str, " "); 
          }
      }
      strcat(str, "     |"); 
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }


  Paint in the description area *
  screen_area_clear(ge->descript);
  for(i=0; i < n_objects; i++){
    if ((obj_loc = game_get_object_location(game, game_get_object_id(game, i) )) != NO_ID) {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
    }
  }
  Paint in the banner area *
  screen_area_puts(ge->banner, " The haunted castle game ");

  /Paint in the help area *
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, attack or a, chat or c, take or t, drop or d, exit or e,");
  screen_area_puts(ge->help, str);

  Paint in the feedback area *
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  Dump to the terminal *
  screen_paint();
  printf("prompt:> ");
*/