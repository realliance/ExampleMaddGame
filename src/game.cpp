#include "game.h"
#include "cube.h"
#include "plane.h"
#include "gamecamera.h"
#include <rendering/shadersystem.h>
#include <event/keyboardeventsystem.h>
#include <event/mouseeventsystem.h>
#include <rendering/rendersystem.h>
#include <rendering/texturesystem.h>
#include <rendering/meshsystem.h>
#include <camerasystem.h>
#include <assets/freecamsystem.h>

Game::Game(){
    const char *title = "test";
    Madd::GetInstance().Init(800, 600, title);
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
}

void Game::Run(){
    while(Madd::GetInstance().StayOpen()){
        Madd::GetInstance().Tick();
    }
}
