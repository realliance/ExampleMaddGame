#include "game.h"
#include "gameobject.h"
#include "cube.h"
#include "plane.h"
#include "gamecamera.h"
#include <rendering/shaderprogram.h>

Game::Game(){
    const char *title = "test";
    Madd::GetInstance().Init(800, 600, title);
    GameObject* cube = new Cube();
    GameObject* plane = new Plane();
    GameObject* gameCamera = new GameCamera();
    Madd::GetInstance().AddObject(gameCamera);
    Madd::GetInstance().AddObject(cube);
    Madd::GetInstance().AddObject(plane);
}

void Game::Run(){
    while(Madd::GetInstance().StayOpen()){
        Madd::GetInstance().Tick();
    }
}
