#include "gamecamera.h"
#include "madd.h"
#include "systems.h"
#include "simplex.h"

#include <components/windowcomponent.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main(){
  
  Madd::GetInstance().Init();
  
  Madd::GetInstance().Register({
    new GlfwSystem,    new RenderSystem ,new TextureSystem,
    new ShaderSystem,  new MeshSystem,   new MouseEventSystem,
    new KeyboardEventSystem,             new CameraSystem, 
    new FreeCamSystem, new BlockSystem,  new InstanceRenderSystem
  });

  // GlfwSystem::EnableDebuggingContext();

  Madd::GetInstance().InitSystems();


  GameCamera* gameCamera = new GameCamera();
  WindowComponent mainWindow{};
  mainWindow.height = 9*64;
  mainWindow.width = 16*64;
  mainWindow.title = "ExampleMaddGame";
  mainWindow.cameras.push_back(&gameCamera->camera.camera);
  Madd::GetInstance().GetSystem("GlfwSystem")->Register(&mainWindow);
  gameCamera->camera.movementSpeed = 4.f;

  {
    int size = 512;
    float stretch = 64.f;
    int magnitude = 16;

    glm::vec2 offsets[] = {{-1,0},{1,0},{0,-1},{0,1}};
    Simplex s = Simplex(8); //as chosen by dice roll;
    gameCamera->camera.camera.pos.y = (s.Noise(0,0)*magnitude)+magnitude+2;
    System* blockSys = Madd::GetInstance().GetSystem("BlockSystem");
//*
    for(int x = -size; x < size; x++){
      for(int z = -size; z < size; z++){
        double y = (s.Noise(x/stretch,z/stretch)*magnitude)+magnitude;
        BlockComponent b = BlockComponent{glm::vec3(x,y,z)};
        blockSys->Register(&b);
        int lowest = y;
        for(const auto & offset: offsets){
          int by = floor(s.Noise((x+offset.x)/stretch,(z+offset.y)/stretch)*magnitude)+magnitude;
          if(by < lowest){
            lowest = by;
          }
        }
        for(int sy = lowest; sy < y; sy++){
          BlockComponent sb = BlockComponent{glm::vec3(x,sy,z)};
          blockSys->Register(&sb);
        }
      }
    }
//*/
  }

  Madd::GetInstance().Run();
  Madd::GetInstance().Deinit();
  delete gameCamera;


  return 0;
}

