#ifndef __SAVEGAME
#define __SAVEGAME

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void save(match *m,const char *file);

void load(match *m,const char *file);

#endif