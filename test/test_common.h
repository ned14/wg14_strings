#pragma once

#include "wg14_strings/config.h"

#include <stdio.h>
#include <stdlib.h>

#define STRINGISE(x) #x
#define CHECK(x)                                                               \
  if(!(x))                                                                     \
  {                                                                            \
    fprintf(stderr, "CHECK(" STRINGISE(x) ") failed at " __FILE__ ":%d\n",     \
            __LINE__);                                                         \
    ret++;                                                                     \
  }
