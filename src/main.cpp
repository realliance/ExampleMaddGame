#include "cube.h"
#include "plane.h"
#include "gamecamera.h"
#include "madd.h"
#include "systems.h"

#include <components/windowcomponent.h>

int main(){
  Madd::GetInstance().Init();
  
  Madd::GetInstance().Register(new WindowSystem);

  Madd::GetInstance().Register(&RenderSystem::GetInstance());
  Madd::GetInstance().Register(new TextureSystem);
  Madd::GetInstance().Register(new ShaderSystem);
  Madd::GetInstance().Register(new MeshSystem);


  Madd::GetInstance().Register(&MouseEventSystem::GetInstance());
  Madd::GetInstance().Register(&KeyboardEventSystem::GetInstance());
  Madd::GetInstance().Register(new CameraSystem);
  Madd::GetInstance().Register(new FreeCamSystem);
  GameCamera* gameCamera = new GameCamera();
  Cube* cube = new Cube();
  Plane* plane = new Plane();

  // mainWindow.update = true;
  WindowComponent mainWindow{};
  mainWindow.height = 600;
  mainWindow.width = 800;
  mainWindow.title = "ExampleMaddGame";
  mainWindow.cameras.push_back(&gameCamera->camera.camera);
  mainWindow.update = true;

  Madd::GetInstance().GetSystem("WindowSystem")->Register(&mainWindow);

  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;
  delete cube;
  delete plane;

  return 0;
}

