#pragma once

#include <string>
#include <vector>

#include <system.h>
#include "blockcomponent.h"
#include <unordered_map>
#include <unordered_set>
#include "glm/gtx/hash.hpp"

#include <texturesystem.h>
#include <meshsystem.h>
#include <shadersystem.h>
#include <rendersystem.h>
#include <instancerendersystem.h>


typedef ComponentID BlockReferenceID;

struct BlockInstance {
  InstanceRenderedComponent r;
};

class BlockSystem : public System {
public:
  void Init();
  ~BlockSystem();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::vector<ComponentType> Types() { return {BlockComponent{}.Type()};}
  std::string Name() { return "BlockSystem"; }
  std::vector<std::string> Requires() {return {"MeshSystem", "ShaderSystem", "InstanceRenderSystem"};};
private:
  std::vector<BlockComponent*> blocks;
  std::unordered_map<BlockReferenceID,BlockInstance> binstance;
  std::unordered_set<glm::vec3> positions;
  MeshComponent mesh;
  ShaderComponent shader;

  TextureSystem* textureSys;
  MeshSystem* meshSys;
  ShaderSystem* shaderSys;
  RenderSystem* renderSys;
  InstanceRenderSystem* instancerenderSys;
};
