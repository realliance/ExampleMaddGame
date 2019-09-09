#pragma once
#include <components/renderedcomponent.h>
#include <components/meshcollidercomponent.h>
#include <components/meshcomponent.h>
#include <components/shadercomponent.h>
#include <vector>
#include <glm/glm.hpp>

class Cube{
public:
  Cube();
  ~Cube();
  bool Render();
  bool Update();
  bool ReloadShaders();
private:
  RenderedComponent cubes[11];
  MeshComponent mesh;
  ShaderComponent shader;
  MeshColliderComponent colliderA;
  MeshColliderComponent colliderB;
  std::vector<glm::vec3> cubePositions;
  TextureComponent textures[2];
};

