#pragma once

#include <string>
#include <vector>

#include "system.h"
#include "blockcomponent.h"
#include "worldcomponent.h"
#include "simplex.h"
#include <unordered_map>

struct WorldInfo {
  int xpos;
  int zpos;
  bool finished;
  std::vector<BlockComponent> blocks;
  Simplex s;
};

class BlockSystem;
class WorldSystem : public System {
  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "WorldSystem"; }
  std::vector<std::string> Requires() {return {"BlockSystem"};};
private:
  BlockSystem* blocksys;
  std::vector<WorldComponent*> worlds;
  std::unordered_map<ComponentID, WorldInfo> info;
};