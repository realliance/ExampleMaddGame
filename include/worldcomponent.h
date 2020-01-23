#pragma once

#include "components/component.h"
#include <sys/types.h>

struct WorldComponent : public Component{
  glm::vec3 size;
  std::string seed;
};

