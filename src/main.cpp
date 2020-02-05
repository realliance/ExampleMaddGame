#include "gamecamera.h"
#include "madd.h"
#include "systems.h"

#include <components/windowcomponent.h>
#include "worldcomponent.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main(){
  
  Madd::GetInstance().Init();
  
  Madd::GetInstance().Register({
    new GlfwSystem,    //new RenderSystem ,//new TextureSystem,
    new ShaderSystem,  new MeshSystem,   new MouseEventSystem,
    new KeyboardEventSystem,             new CameraSystem, 
    new FreeCamSystem, new BlockSystem,  new InstanceRenderSystem,
    new SimplexSystem, new WorldSystem,  new RenderSystem
  });

  // GlfwSystem::EnableDebuggingContext();

  if(!Madd::GetInstance().InitSystems()){
    std::cout << "Madd failed to start." << std::endl;
    return 1;
  }


  GameCamera* gameCamera = new GameCamera();
  WindowComponent mainWindow{};
  mainWindow.height = 9*64;
  mainWindow.width = 16*64;
  mainWindow.title = "ExampleMaddGame";
  mainWindow.cameras.push_back(&gameCamera->camera.camera);
  Madd::GetInstance().GetSystem("GlfwSystem")->Register(&mainWindow);
  gameCamera->camera.movementSpeed = 16.f;

  WorldComponent world{};
  world.stretch = {256, 128, 256};
  world.size = {256,256};
  world.seed = "test_seed";
  Madd::GetInstance().GetSystem("WorldSystem")->Register(&world);

  MeshComponent mesh;
  mesh.modelPath = "fruits.obj";
  if(!dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"))->Register(&mesh)){
    throw ("Mesh loading failed");
  }

  ShaderComponent shader;
  shader.fragmentShaderPath = "default.fs";
  shader.vertexShaderPath = "default.vs";
  shader.enableCulling = true;
  dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"))->Register(&shader);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,{-40.f,10.f,0.f});

  RenderedComponent r = RenderedComponent(
    &mesh, //MeshComponent
    nullptr, //Texture nullptr will be interpreted as no texture
    &shader, //ShaderComponent
    model, //Model aka position, size, and rotation 
    glm::vec4(0.3f, 0.4f, 0.6f, 1.f) //Shade
  );

  dynamic_cast<RenderSystem*>(Madd::GetInstance().GetSystem("RenderSystem"))->Register(&r);

  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;


  return 0;
}

