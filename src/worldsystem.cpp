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
  // for (TemplateSystem *t : objects) {

  // }
}