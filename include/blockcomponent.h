#pragma once

#include <component.h>
#include <sys/types.h>
#include <glm/glm.hpp>

struct BlockComponent : public Component{
  BlockComponent(glm::vec3 position) : position(position){}
  BlockComponent():position(glm::vec3(0.f)){}
  glm::vec3 position;
  ComponentType Type(); 
  private: static ComponentType cType;
};

