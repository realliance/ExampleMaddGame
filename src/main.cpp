#include "gamecamera.h"
#include "madd.h"
#include "systems.h"

#include <components/windowcomponent.h>
#include "worldcomponent.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main(){
  try{
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

    KeyboardEventComponent exitEvent = KeyboardEventComponent{};
    exitEvent.callback = [](Component* c, WindowComponent* window, int key, int action){Madd::GetInstance().Close();};
    exitEvent.code = KEY_ESCAPE;
    Madd::GetInstance().RegisterComponent(&exitEvent);

    GameCamera* gameCamera = new GameCamera();
    WindowComponent mainWindow{};
    mainWindow.height = 9*64;
    mainWindow.width = 16*64;
    mainWindow.title = "ExampleMaddGame";
    mainWindow.cameras.push_back(&gameCamera->camera.camera);
    Madd::GetInstance().RegisterComponent(&mainWindow);
    gameCamera->camera.movementSpeed = 16.f;

    WorldComponent world{};
    world.stretch = {256, 128, 256};
    world.size = {256,256};
    world.seed = "test_seed";
    Madd::GetInstance().RegisterComponent(&world);

    MeshComponent mesh;
    mesh.modelPath = "fruits.obj";
    if(!Madd::GetInstance().RegisterComponent(&mesh)){
      throw ("Mesh loading failed");
    }

    ShaderComponent shader;
    shader.fragmentShaderPath = "default.fs";
    shader.vertexShaderPath = "default.vs";
    shader.enableCulling = true;
    Madd::GetInstance().RegisterComponent(&shader);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,{-40.f,10.f,0.f});

    RenderedComponent r = RenderedComponent(
      &mesh, //MeshComponent
      nullptr, //Texture nullptr will be interpreted as no texture
      &shader, //ShaderComponent
      model, //Model aka position, size, and rotation 
      glm::vec4(0.3f, 0.4f, 0.6f, 1.f) //Shade
    );

    Madd::GetInstance().RegisterComponent(&r);

    Madd::GetInstance().Run();
    Madd::GetInstance().Deinit();
    delete gameCamera;
  }catch(const char* s){
    std::cout << "Exception Occured: " << s << std::endl;
    return 1;
  }catch(std::string s){
    std::cout << "Exception Occured: " << s << std::endl;
    return 1;
  }
  return 0;
}
