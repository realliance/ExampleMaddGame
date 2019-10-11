#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include <madd.h>
#include <collider.h>
#include <algorithm>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <texturesystem.h>

glm::mat4 getModel(int i, const glm::vec3& pos){
  glm::mat4 model = glm::mat4(1.0f);
  glm::vec3 offset = {3.0f,3.0f,3.0f};
  model = glm::translate(model, pos+offset);//+{glm::sin(Madd::GetInstance().GetTime()+i*20.f}/10.f,0.f,0.f});
  float angle = Madd::GetInstance().GetTime()/10.f + glm::radians(i*20.0f);
  glm::vec3 axis = {1.0f, 0.3f, 0.5f};
  model = glm::rotate(model, angle, axis);
  return model;
}

Cube::Cube() {
  std::vector<glm::vec3> verts = {
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
  
  cubePositions = {
    { 0.0f,  0.0f,  0.0f}, { 2.0f,  5.0f, -1.0f}, {-1.5f, -2.2f, -2.5f},  
    {-3.8f, -2.0f, -2.3f}, { 2.4f, -0.4f, -3.5f}, {-1.7f,  3.0f, -3.5f},  
    { 1.3f, -2.0f, -2.5f}, { 1.5f,  2.0f, -2.5f}, { 1.5f,  0.2f, -1.5f}, 
    {-1.3f,  1.0f, -1.5f}, { 0.0f,  0.0f,  1.4f}
  };
  std::vector<glm::vec3> collisionMesh = {
    { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f}
  };

  std::vector<glm::vec2> texcoords = {
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

  textures[0].filename = "container.jpg";
  textures[1].filename = "logo.png";
  Madd::GetInstance().GetSystem("TextureSystem")->Register(&textures[0]);
  Madd::GetInstance().GetSystem("TextureSystem")->Register(&textures[1]);

  mesh.verts = verts;
  mesh.texcoords = texcoords;
  Madd::GetInstance().GetSystem("MeshSystem")->Register(&mesh);

  shader.fragmentShaderPath = "default.fs";
  shader.vertexShaderPath = "default.vs";
  Madd::GetInstance().GetSystem("ShaderSystem")->Register(&shader);

  for(int i = 0; i < 11; i++){
    cubes[i] = RenderedComponent{};
    cubes[i].texture = &textures[i % 2];
    cubes[i].shade = glm::vec4(1.f);
    cubes[i].mesh = &mesh;
    cubes[i].shader = &shader;
    cubes[i].model = getModel(i,cubePositions[i]);
    Madd::GetInstance().GetSystem("RenderSystem")->Register(&cubes[i]);
  }

  colliderA = MeshColliderComponent{};
  colliderA.mesh = &mesh;
  colliderB = colliderA;

}

void Cube::Unregister(){
  for(int i = 0; i < 11; i++){
    Madd::GetInstance().GetSystem("RenderSystem")->Unregister(&cubes[i]);
  }
  Madd::GetInstance().GetSystem("ShaderSystem")->Unregister(&shader);
  Madd::GetInstance().GetSystem("TextureSystem")->Unregister(&textures[0]);
  Madd::GetInstance().GetSystem("TextureSystem")->Unregister(&textures[1]);
  Madd::GetInstance().GetSystem("MeshSystem")->Unregister(&mesh);
}

