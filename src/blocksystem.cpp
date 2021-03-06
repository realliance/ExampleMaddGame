#include "blocksystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "madd.h"

SystemType BlockSystem::sType = Madd::GetNewSystemType();

void BlockSystem::Init() {
  instancerenderSys = Madd::GetInstance().GetSystem<InstanceRenderSystem>();

  mesh.modelPath = "cube.obj";
  if(!Madd::GetInstance().RegisterComponent(&mesh)){
    throw ("Mesh loading failed");
  }
  InstanceConfig c;
  c.instancedshade = false;
  c.simplemodel = true;
  c.updatemodel = false;
  instancerenderSys->SetConfig(c,&mesh);

  shader.fragmentShaderPath = "instanceblock.fs";
  shader.vertexShaderPath = "instanceblock.vs";
  shader.enableCulling = true;
  Madd::GetInstance().RegisterComponent(&shader);
}

void BlockSystem::Deinit(){
    std::cout << blocks.size() << std::endl;
}

bool BlockSystem::Register(Component* component){
  BlockComponent* b = dynamic_cast<BlockComponent*>(component);
  b->position = glm::floor(b->position);
  if(positions.contains(b->position)){
    std::cout << "Failed to place block at: " << glm::to_string(b->position) << std::endl;
    return false;
  }
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,b->position);
  InstanceRenderedComponent r = InstanceRenderedComponent(
    &mesh, //MeshComponent
    nullptr, //Texture nullptr will be interpreted as no texture
    &shader, //ShaderComponent
    model, //Model aka position, size, and rotation 
    glm::vec4(0.3f, 0.4f, 0.6f, 1.f) //Shade
  );
    
  
  BlockInstance binst = BlockInstance{};
  binst.r = r;

  binstance[component->cID] = binst;
  if(!Madd::GetInstance().RegisterComponent(&binstance[component->cID].r)){
    binstance.erase(component->cID);
    return false;
  }

  positions.insert(b->position);
  blocks.push_back(dynamic_cast<BlockComponent*>(component));
  

  return true;
}



bool BlockSystem::Unregister(Component* component){
  for(auto i = begin(blocks); i != end(blocks); i++){
    if((*i)->cID == component->cID){
      instancerenderSys->Unregister(&binstance[component->cID].r);
      binstance.erase(component->cID);
      blocks.erase(i);
      positions.erase(dynamic_cast<BlockComponent*>(component)->position);
      return true;
    }
  }
  return false;
}

void BlockSystem::Update(){
  // for (BlockComponent *t : blocks) {

  // }
}
