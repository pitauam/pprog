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

#define WIDTH_MAP 90
#define WIDTH_DES 37
#define WIDTH_BAN 25
#define HEIGHT_MAP 34
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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right = NO_ID, id_left = NO_ID, obj_loc = NO_ID, char_id = NO_ID, char_loc = NO_ID, player_object_id = NO_ID;
  Character *character;
  Player *player;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int n_objects;
  int i = 0; 

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    n_objects = game_get_number_of_objects(game);

    /*0 for north, previous space*/
    id_back = game_get_connection(game, id_act, 0);
    id_next = game_get_connection(game, id_act, 1);
    id_right = game_get_connection(game, id_act, 2);
    id_left = game_get_connection(game, id_act, 3);


      /*imprime el anterior*/
    if (id_back != NO_ID) {
      graphic_engine_space_place(ge, game, id_back);
      sprintf(str, "                                ^");
      screen_area_puts(ge->map, str);
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
      sprintf(str, "                                v");
      screen_area_puts(ge->map, str);
      graphic_engine_space_place(ge, game, id_next);
    }


  /* Paint in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, " Objects :");
  screen_area_puts(ge->descript, str);
  for(i=0; i < n_objects; i++){
    if ((obj_loc = game_get_object_location(game, game_get_object_id(game, i) )) != NO_ID) {
    
    sprintf(str, "    %5s:% 3d", (game_get_object_name(game, game_get_object(game, game_get_object_id(game, i)))), (int)obj_loc);
    
    screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, " Characters :");
  screen_area_puts(ge->descript, str);
  for(i=0; i < game_get_number_of_spaces(game); i++){
    /*char_id = game_get_character_location(game, game_get_character_id(game, game_get_space_id_at(game, i)));*/

    char_id = game_get_character_id(game, game_get_space_id_at(game, i));
    
    if (char_id != NO_ID) 
    {
      char_loc = game_get_space_id_at(game,i);

      character = game_get_character(game, char_id);

      sprintf(str, "%9s (%3s):% 3d (%i)", (character_get_name(character)),character_get_description(character), (int)char_loc, character_get_health(character));
    
      screen_area_puts(ge->descript, str);
    }
  }

  player = game_get_player(game);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, " Player : %3d (%d)", (int)id_act, player_get_health(player));

  screen_area_puts(ge->descript, str);
  
  if(player_inventory_empty(player) == FALSE){
  sprintf(str,"Player carries object: ");
    for(i=0; i < player_get_n_objects(player); i++){
      player_object_id = player_get_object_id(player, i);
      if (player_object_id != NO_ID) {
        sprintf(str, "%ld", player_object_id);
      } else {
      sprintf(str, "No object in the player's inventory.\n");
      }
    }
    
  }

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
  screen_area_puts(ge->descript, str);
  
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
  sprintf(str, "     next or n, back or b, left or l, right or r, attack or a, chat or c, take or t, drop or d, exit or e,");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL],cmd_to_str[last_cmd - NO_CMD][CMDS], command_get_return(game_get_last_command(game)));
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint(RED);
  printf("prompt:> ");
  }
}

/*prints -x-*/
void graphic_engine_space_place(Graphic_engine *ge,Game *game, Id id_act){
  char str[255];
  char obj[100];
  char name_char[100];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len;
  char *gdesc;

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
  /*prints the characters*/
  strcpy(str, "                       |          ");
  if (game_get_character_id(game, id_act) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_act))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  

  strcat(str, "     |");
  screen_area_puts(ge->map, str);
  sprintf(str, "                       |                  |");

for (j = 0; j < 5; j++) 
  {
    gdesc = space_get_gdesc_line(game_get_space(game, id_act), j);

    if (gdesc != NULL && gdesc[0] != '\0') 
    {
        sprintf(str, "                       | %-9.9s        |", gdesc);
    } else {
        sprintf(str, "                       |                  |");
    }
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
  char name_char[100];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len1;
  int len2;
  char *gdesc_left;
  char *gdesc_act;
  char part_left[35];
  char part_act[35];
  char sep[4] = "   ";

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
  /*prints the characters*/
  
  strcpy(str, "|          ");
  if (game_get_character_id(game, id_left) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_left))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  

  strcat(str, "     |   |          ");
  if (game_get_character_id(game, id_act) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_act))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  strcat(str, "     |");
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  |   |                  |");

  for (j = 0; j < 5; j++) {
      gdesc_left = space_get_gdesc_line(game_get_space(game, id_left), j);
      gdesc_act = space_get_gdesc_line(game_get_space(game, id_act), j);
      
      if (gdesc_left != NULL && gdesc_left[0] != '\0') {
          sprintf(part_left, "| %-9.9s        |", gdesc_left);
      } else {
          sprintf(part_left, "|                  |");
      }

      if (gdesc_act != NULL && gdesc_act[0] != '\0') {
          sprintf(part_act, "| %-9.9s        |", gdesc_act);
      } else {
          sprintf(part_act, "|                  |");
      }

      strcpy(sep, "   ");
      /*if it is in the middle of the drawing*/
      if (j == 2) 
      {
        strcpy(sep, " < "); 
      }
      
      sprintf(str, "%s%s%s", part_left, sep, part_act);
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
  char name_char[100];
  Id player_location;
  int n_objects;
  int i;
  int j;
  char *gdesc_l;
  char *gdesc_a;
  char *gdesc_r;
  char p_l[35];
  char p_a[35];
  char p_r[35];
  char sep_l[4];
  char sep_r[4];


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
  /*prints the characters*/
  strcpy(str, "|          ");
  if (game_get_character_id(game, id_left) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_left))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  

  strcat(str, "     |   |          ");
  if (game_get_character_id(game, id_act) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_act))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  strcat(str, "     |   |          ");
  if (game_get_character_id(game, id_right) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_right))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  strcat(str, "     |");
  screen_area_puts(ge->map, str);
  sprintf(str, "|                |   |                |   |                |");

  for (j = 0; j < 5; j++) {
      gdesc_l = space_get_gdesc_line(game_get_space(game, id_left), j);
      gdesc_a = space_get_gdesc_line(game_get_space(game, id_act), j);
      gdesc_r = space_get_gdesc_line(game_get_space(game, id_right), j);

      if (gdesc_l != NULL && gdesc_l[0] != '\0') sprintf(p_l, "| %-9.9s        |", gdesc_l);
      else sprintf(p_l, "|                  |");

      if (gdesc_a != NULL && gdesc_a[0] != '\0') sprintf(p_a, "| %-9.9s        |", gdesc_a);
      else sprintf(p_a, "|                  |");

      if (gdesc_r != NULL && gdesc_r[0] != '\0') sprintf(p_r, "| %-9.9s        |", gdesc_r);
      else sprintf(p_r, "|                  |");

      strcpy(sep_l, "   ");
      strcpy(sep_r, "   ");

      /* if it is drawing the middle of the drawing*/
      if (j == 2) {
          strcpy(sep_l, " < ");
          strcpy(sep_r, " > ");
      }
      /* Joins together all spaces and prints them*/
      sprintf(str, "%s%s%s%s%s", p_l, sep_l, p_a, sep_r, p_r);
      screen_area_puts(ge->map, str);
      
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
  char name_char[100];
  Id player_location;
  int n_objects;
  int i;
  int j;
  int len1;
  int len2;
  char *gdesc_act;
  char *gdesc_right;
  char p_a[35];
  char p_r[35];
  char sep[4];

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
  /*prints the characters*/
  sprintf(str, "                       |             ");
  if (game_get_character_id(game, id_act) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_act))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  strcat(str, "  |   |             ");

  if (game_get_character_id(game, id_right) != NO_ID)
  {
    strcpy(name_char, character_get_description(game_get_character(game, game_get_character_id(game, id_right))));
    strcat(str, name_char);
  }
  else {
    strcat(str, "   ");
  }
  strcat(str, "  |");
  screen_area_puts(ge->map, str);
  sprintf(str, "                       |                  |   |                  |");

  for (j = 0; j < 5; j++) {
      gdesc_act = space_get_gdesc_line(game_get_space(game, id_act), j);
      gdesc_right = space_get_gdesc_line(game_get_space(game, id_right), j);
      
      if (gdesc_act != NULL && gdesc_act[0] != '\0') sprintf(p_a, "| %-9.9s        |", gdesc_act);
      else sprintf(p_a, "|                  |");

      if (gdesc_right != NULL && gdesc_right[0] != '\0') sprintf(p_r, "| %-9.9s        |", gdesc_right);
      else sprintf(p_r, "|                  |");

      
      strcpy(sep, "   ");
      if (j == 2) 
      {
        strcpy(sep, " > ");
      }
      
      sprintf(str, "                       %s%s%s", p_a, sep, p_r);
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
