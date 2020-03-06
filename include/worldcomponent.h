#pragma once

#include <components/component.h>
#include <sys/types.h>
#include <glm/glm.hpp>
#include <string>

struct WorldComponent : public Component{
  glm::vec2 size;
  glm::vec3 stretch;
  std::string seed;
  ComponentType Type(); 
  private: static ComponentType cType;
};

