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

    KeyboardEventComponent exitEvent = KeyboardEventComponent{};
    exitEvent.callback = [](Component* c, WindowComponent* window, int key, int action){
      Madd::GetInstance().Close();
    };
    exitEvent.code = KEY_ESCAPE;
    GameCamera* gameCamera = new GameCamera();
    WindowComponent window{};
    window.height = 9*64;
    window.width = 16*64;
    window.title = "ExampleMaddGame";
    window.cameras.push_back(&gameCamera->camera.camera);
    Madd::GetInstance().CreateEntity({&exitEvent,&window});

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
    
    Entity fruits = {&mesh,&shader,&r};
    EntityID fruitID = Madd::GetInstance().CreateEntity({&mesh,&shader,&r});
        
    KeyboardEventComponent deleteFruitEvent = KeyboardEventComponent{};
    KeyboardEventComponent createFruitEvent = KeyboardEventComponent{};

    bool fruitdeleted = false;
    deleteFruitEvent.callback = [&fruitdeleted,&fruitID](Component* c, WindowComponent* window, int key, int action) mutable{
      if(action != KEY_PRESS){
        return;
      }
      if(Madd::GetInstance().DeleteEntity(fruitID)){
        fruitdeleted = true;
        std::cout << "Fruit Deleted" << std::endl;
      }else{
        std::cout << "Fruit already Deleted." << std::endl;
      }
    };
    deleteFruitEvent.code = KEY_0;
    createFruitEvent.callback = [&fruitdeleted,&fruitID,&fruits](Component* c, WindowComponent* window, int key, int action) mutable{
      if(action != KEY_PRESS){
        return;
      }
      if(fruitdeleted){
        fruitID = Madd::GetInstance().CreateEntity(fruits);
        fruitdeleted = false;
        std::cout << "Fruit Created" << std::endl;
      }else{
        std::cout << "Fruit already created" << std::endl;
      }
    };
    createFruitEvent.code = KEY_9;
    Madd::GetInstance().CreateEntity({&deleteFruitEvent,&createFruitEvent});

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
