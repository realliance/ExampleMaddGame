#pragma once

#include <component.h>
#include <sys/types.h>
#include <string>
#include <glm/glm.hpp>

struct SimplexComponent : public Component{
  std::string seed;
  glm::vec3 size;
  ComponentType Type(); 
  private: static ComponentType cType;
};

