#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

Object* object_create(Id id);

Status object_destroy(Object* object);

Id object_get_id(Object* object);

Status object_set_name(Object* object, char* name);

const char* object_get_name(Object* object);

Status object_print(Object* object);

#endif