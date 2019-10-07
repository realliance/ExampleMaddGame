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
  
  Madd::GetInstance().Register({
    new GlfwSystem,&RenderSystem::GetInstance(),new TextureSystem,
    new ShaderSystem, new MeshSystem, &MouseEventSystem::GetInstance(),
    &KeyboardEventSystem::GetInstance(), new CameraSystem, 
    new FreeCamSystem
  });

  Madd::GetInstance().InitSystems();


  GameCamera* gameCamera = new GameCamera();
  WindowComponent mainWindow{};
  mainWindow.height = 600;
  mainWindow.width = 800;
  mainWindow.title = "ExampleMaddGame";
  mainWindow.cameras.push_back(&gameCamera->camera.camera);
  Madd::GetInstance().GetSystem("GlfwSystem")->Register(&mainWindow);


  CameraComponent secondary = CameraSystem::Construct();
  secondary.pos = {0.f,10.f,0.f};
  secondary.up = {1.0f,0.f,0.f};
  secondary.front = {0.0f,-1.f,0.f};
  secondary.lookAt = {0.f,-1.f,0.f};
  Madd::GetInstance().GetSystem("CameraSystem")->Register(&secondary);
  WindowComponent secondwindow{};
  secondwindow.height = 300;
  secondwindow.width = 400;
  secondwindow.title = "Second";
  secondwindow.cameras.push_back(&secondary);
  Madd::GetInstance().GetSystem("GlfwSystem")->Register(&secondwindow);

  Cube* cube = new Cube();
  Plane* plane = new Plane();

  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;
  delete cube;
  delete plane;

  return 0;
}

