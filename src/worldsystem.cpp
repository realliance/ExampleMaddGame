#include "worldsystem.h"
#include "madd.h"
#include "blocksystem.h"
#include "simplexsystem.h"


void WorldSystem::Init() {
  blocksys = dynamic_cast<BlockSystem*>(Madd::GetInstance().GetSystem("BlockSystem"));
  simplexsys = dynamic_cast<SimplexSystem*>(Madd::GetInstance().GetSystem("SimplexSystem"));
}

void WorldSystem::Deinit(){

}

bool WorldSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  WorldComponent* w = dynamic_cast<WorldComponent*>(component);
  worldinfo[component->cID] = WorldInfo{};
  WorldInfo* wi = &worldinfo[component->cID];
  wi->xpos = -w->size.x;
  wi->zpos = -w->size.y;
  wi->finished = false;
  wi->rand = SimplexComponent{};
  wi->rand.seed = w->seed;
  wi->rand.size = w->stretch;
  wi->world = w;
  simplexsys->Register(&wi->rand);  
  return true;
}


bool WorldSystem::Unregister(Component* component){
  if(!worldinfo.contains(component->cID)){
    return false;
  }
  simplexsys->Unregister(&worldinfo[component->cID].rand);
  worldinfo.erase(component->cID);
  return true;
}

void WorldSystem::Update(){
  for (auto &[cID,info] : worldinfo) {
    if(!info.finished){
      placeBlocks(info);
    }
  }
}

void WorldSystem::placeBlocks(WorldInfo& info){
  size_t placed = 0;
  for(int x = info.world->size.x; info.xpos < x; info.xpos++){
    for(int z = info.world->size.y; info.zpos < z; info.zpos++){
      processXZBlock(info.xpos,info.zpos,info);
      if(placed > 1024){
        return;
      }
        placed++;
    }
    info.zpos = -info.world->size.y;
  }
  info.finished = true;
}

void WorldSystem::processXZBlock(int x, int z, WorldInfo& info){
  int y = getY(x, z, info);
  info.blocks.push_back(BlockComponent{glm::vec3(x,y,z)});
  blocksys->Register(&info.blocks.back());
  processDepth({x,y,z},info);
}

void WorldSystem::processDepth(glm::vec3 pos, WorldInfo& info){
  const glm::vec2 offsets[] = {{-1,0},{1,0},{0,-1},{0,1}};
  int lowest = pos.y;
  for(const auto & offset: offsets){
    int by = getY(pos.x+offset.x,pos.z+offset.y, info);
    if(by < lowest){
      lowest = by;
    }
  }
  for(int sy = lowest+1; sy < pos.y; sy++){
    info.blocks.push_back(BlockComponent{glm::vec3(pos.x,sy,pos.z)});
    blocksys->Register(&info.blocks.back());
  }
}

int WorldSystem::getY(int x, int z, WorldInfo& info){
  return floor(
    simplexsys->Noise(x, z) *
    glm::sin((x)/info.world->size.x) *
    glm::cos((z)/info.world->size.y)
  );
}
