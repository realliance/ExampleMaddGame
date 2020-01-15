#pragma once

#include "components/component.h"
#include <sys/types.h>

struct WorldComponent : public Component{
  int size;
  int stretch;
  int magnitude;
  int seed;
};

