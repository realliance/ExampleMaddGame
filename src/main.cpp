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
    
    Madd::GetInstance().LoadSystems({
      new GlfwSystem,    //new RenderSystem ,//new TextureSystem,
      new ShaderSystem,  new MeshSystem,   new MouseEventSystem,
      new KeyboardEventSystem,             new CameraSystem, 
      new FreeCamSystem, new BlockSystem,  new InstanceRenderSystem,
      new SimplexSystem, new WorldSystem,  new RenderSystem
    });

    // GlfwSystem::EnableDebuggingContext();

    Madd::GetInstance().InitSystems();

    KeyboardEventComponent exitCB = KeyboardEventComponent{};
    exitCB.callback = [](Component* c, WindowComponent* window, int key, int action){Madd::GetInstance().Close();};
    exitCB.code = KEY_ESCAPE;
    GameCamera* gameCamera = new GameCamera();
    WindowComponent window{};
    window.height = 9*64;
    window.width = 16*64;
    window.title = "ExampleMaddGame";
    window.cameras.push_back(&gameCamera->camera.camera);

    Entity mainWindow{&exitCB,&window};
    Madd::GetInstance().CreateEntity(&mainWindow);

    gameCamera->camera.movementSpeed = 16.f;

    WorldComponent world{};
    world.stretch = {256, 128, 256};
    world.size = {256,256};
    world.seed = "test_seed";
    Madd::GetInstance().RegisterComponent(&world);

    MeshComponent mesh;
    mesh.modelPath = "fruits.obj";
    ShaderComponent shader;
    shader.fragmentShaderPath = "default.fs";
    shader.vertexShaderPath = "default.vs";
    shader.enableCulling = true;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,{-40.f,10.f,0.f});
    RenderedComponent r = RenderedComponent(
      &mesh, //MeshComponent
      nullptr, //Texture nullptr will be interpreted as no texture
      &shader, //ShaderComponent
      model, //Model aka position, size, and rotation 
      glm::vec4(0.3f, 0.4f, 0.6f, 1.f) //Shade
    );
    
    Entity fruits{&mesh,&shader,&r};
    Madd::GetInstance().CreateEntity(&fruits);

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
