#include "cube.h"
#include "plane.h"
#include "gamecamera.h"
#include "madd.h"
#include "systems.h"

#include <components/windowcomponent.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main(){
  Madd::GetInstance().Init();
  
  Madd::GetInstance().Register(new GlfwSystem);

  Madd::GetInstance().Register(&RenderSystem::GetInstance());
  Madd::GetInstance().Register(new TextureSystem);
  Madd::GetInstance().Register(new ShaderSystem);
  Madd::GetInstance().Register(new MeshSystem);


  Madd::GetInstance().Register(&MouseEventSystem::GetInstance());
  Madd::GetInstance().Register(&KeyboardEventSystem::GetInstance());
  Madd::GetInstance().Register(new CameraSystem);
  Madd::GetInstance().Register(new FreeCamSystem);

  WindowComponent mainWindow{};
  mainWindow.height = 600;
  mainWindow.width = 800;
  mainWindow.title = "ExampleMaddGame";

  Madd::GetInstance().GetSystem("GlfwSystem")->Register(&mainWindow);
  dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"))->Enable(mainWindow);
  
  GameCamera* gameCamera = new GameCamera();
  Cube* cube = new Cube();
  Plane* plane = new Plane();

  mainWindow.cameras.push_back(&gameCamera->camera.camera);
  mainWindow.update = true;

  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;
  delete cube;
  delete plane;

  return 0;
}

