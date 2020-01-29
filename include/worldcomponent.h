#pragma once

#include "components/component.h"
#include <sys/types.h>

struct WorldComponent : public Component{
  glm::vec2 size;
  glm::vec3 stretch;
  std::string seed;
};

