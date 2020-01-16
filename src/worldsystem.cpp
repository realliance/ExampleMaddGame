#include "worldsystem.h"
#include "madd.h"
#include "blocksystem.h"

void WorldSystem::Init() {
  blocksys = dynamic_cast<BlockSystem*>(Madd::GetInstance().GetSystem("BlockSystem"));
}

void WorldSystem::Deinit(){

}

bool WorldSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  WorldComponent* w = dynamic_cast<WorldComponent*>(component);
  worlds.push_back(dynamic_cast<WorldComponent*>(component));
  info[component->cID] = WorldInfo{};
  WorldInfo* wi = &info[component->cID];
  wi->xpos = -w->size;
  wi->zpos = -w->size;
  wi->finished = false;
  
  return true;
}



bool WorldSystem::Unregister(Component* component){
  for(auto i = begin(worlds); i != end(worlds); i++){
    if((*i)->cID == component->cID){
      worlds.erase(i);
      return true;
    }
  }
  return false;
}

void WorldSystem::Update(){
  for (WorldComponent *wc : worlds) {
    placeBlocks(wc);
  }
}

void WorldSystem::placeBlocks(WorldComponent *wc){
  for(int x = -wc->size; x < wc->size; x++){
      for(int z = -wc->size; z < wc->size; z++){

      }
    }
}

void WorldSystem::processXYBlock(int x, int z, WorldComponent* wc){
  double y = 
  blocks.push_back(BlockComponent{glm::vec3(x,y,z)});
  int lowest = y;
  for(const auto & offset: offsets){
    int by = floor(s.Noise((x+offset.x)/stretch,(z+offset.y)/stretch)*magnitude*glm::sin((x+offset.x)/stretch))+magnitude;
    if(by < lowest){
      lowest = by;
    }
  }
  for(int sy = lowest+1; sy < y; sy++){
    blocks.push_back(BlockComponent{glm::vec3(x,sy,z)});
  }
}

double WorldSystem::getY(int x, int z, WorldComponent* wc){
  floor(s.Noise(x/wc->stretch,z/wc->stretch)*wc->magnitude*glm::sin((x)/wc->stretch))+wc->magnitude;
}
