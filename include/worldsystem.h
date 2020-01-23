#pragma once

#include <string>
#include <vector>

#include "system.h"
#include "blockcomponent.h"
#include "worldcomponent.h"
#include "simplexcomponent.h"
#include "simplexsystem.h"
#include <unordered_map>

struct WorldInfo {
  int xpos;
  int zpos;
  bool finished;
  std::vector<BlockComponent> blocks;
  SimplexComponent rand;
  WorldComponent* world;
};

class SimplexSystem;
class BlockSystem;
class WorldSystem : public System {
public:
  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "WorldSystem"; }
  std::vector<std::string> Requires() {return {"BlockSystem","SimplexSystem"};};
private:
  void placeBlocks(WorldInfo& info);
  void processXZBlock(int x, int z, WorldInfo& info);
  int getY(int x, int z, WorldInfo& info);
  void processDepth(glm::vec3 pos, WorldInfo& info);
  BlockSystem* blocksys;
  SimplexSystem* simplexsys;
  std::unordered_map<ComponentID, WorldInfo> worldinfo;
};
