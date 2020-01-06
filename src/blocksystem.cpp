#include "blocksystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "madd.h"

void BlockSystem::Init() {
  textureSys = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));
  meshSys = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
  shaderSys = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));
  renderSys = dynamic_cast<RenderSystem*>(Madd::GetInstance().GetSystem("RenderSystem"));

  const std::vector<glm::vec3> verts = {
    {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},

    {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},

    {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}
  };

  const std::vector<glm::vec2> texcoords = {
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

    {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},

    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}
  };

  mesh.verts = verts;
  mesh.texcoords = texcoords;
  meshSys->Register(&mesh);

  shader.fragmentShaderPath = "block.fs";
  shader.vertexShaderPath = "block.vs";
  shaderSys->Register(&shader);


}

void BlockSystem::Deinit(){
  for(auto & [bref, binst] : binstance){
    renderSys->Unregister(&binst.r);
  }
  blocks.clear();
  binstance.clear();
  shaderSys->Unregister(&shader);
  meshSys->Unregister(&mesh);
  textureSys = nullptr;
  meshSys = nullptr;
  shaderSys = nullptr;
  renderSys = nullptr;
}

bool BlockSystem::Register(Component* component){
  BlockComponent* b = dynamic_cast<BlockComponent*>(component);
  b->cID = Madd::GetInstance().GetNewComponentID();
  b->position = glm::floor(b->position);
  if(positions.contains(b->position)){
    return false;
  }
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,b->position);
  RenderedComponent r = RenderedComponent(
    &mesh, //MeshComponent
    nullptr, //Texture nullptr will be interpreted as no texture
    &shader, //ShaderComponent
    model, //Model aka position, size, and rotation 
    glm::vec4(0.0f, 0.2f, 0.2f, 1.f)+glm::vec4(glm::abs(b->position)*0.05f, 0.f) //Shade
  );

    
  binstance[component->cID] = BlockInstance{};
  binstance[component->cID].r = r;

  if(!renderSys->Register(&binstance[component->cID].r)){
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
      renderSys->Unregister(&binstance[component->cID].r);
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