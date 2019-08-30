#include "game.h"
#include "cube.h"
#include "plane.h"
#include "gamecamera.h"
#include <rendering/shaderprogram.h>
#include <event/keyboardeventsystem.h>
#include <event/mouseeventsystem.h>
#include <camerasystem.h>
#include <assets/freecamsystem.h>

Game::Game(){
    const char *title = "test";
    Madd::GetInstance().Init(800, 600, title);
    Madd::GetInstance().Register(&MouseEventSystem::GetInstance());
    Madd::GetInstance().Register(&KeyboardEventSystem::GetInstance());
    Madd::GetInstance().Register(new CameraSystem);
    Madd::GetInstance().Register(new FreeCamSystem);
    Cube* cube = new Cube();
    Plane* plane = new Plane();
    GameCamera* gameCamera = new GameCamera();
    // Madd::GetInstance().AddObject(gameCamera);
    // Madd::GetInstance().AddObject(cube);
    // Madd::GetInstance().AddObject(plane);
}

void Game::Run(){
    while(Madd::GetInstance().StayOpen()){
        Madd::GetInstance().Tick();
    }
}
