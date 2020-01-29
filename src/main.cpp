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
    new SimplexSystem, new WorldSystem
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
  world.stretch = {256, 256, 256};
  world.size = {256,256};
  world.seed = "test_seed";
  Madd::GetInstance().GetSystem("WorldSystem")->Register(&world);


  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;


  return 0;
}

