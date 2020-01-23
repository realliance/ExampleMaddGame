#pragma once

#include <components/component.h>
#include <sys/types.h>
#include <string>
#include <glm/glm.hpp>

struct SimplexComponent : public Component{
  std::string seed;
  glm::vec3 size;
};

