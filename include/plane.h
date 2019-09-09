#pragma once
#include <components/renderedcomponent.h>
#include <components/texturecomponent.h>
#include <components/meshcomponent.h>
#include <components/shadercomponent.h>
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Plane{
public:
  Plane();
  ~Plane();
  bool Render();
  bool Update();
  bool ReloadShaders();
private:
  RenderedComponent renderedPlane;
  ShaderComponent shader;
  MeshComponent mesh;
  TextureComponent tex;
};

