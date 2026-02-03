#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

typedef struct _Player Player;


Player* player_create(Id id);

Status player_destroy(Player* player);

Id player_get_id(Player* player);

Status player_set_name(Player* player, char* name);

const char* player_get_name(Player* player);

Status player_set_location(Player* player, Id id);

Id player_get_location(Player* player);

Status player_set_object(Player* player, Id id);

Id player_get_object(Player* player);

Status player_print(Player* player);
#endif
