#include "game.h"
#include "gameobject.h"
#include "cube.h"
#include "plane.h"
#include "gamecamera.h"

Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 600, title);
    GameObject* cube = new Cube(Engine);
    GameObject* plane = new Plane(Engine);
    GameObject* gameCamera = new GameCamera(Engine);
    Engine->AddObject(gameCamera);
    Engine->AddObject(cube);
    Engine->AddObject(plane);    
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->StayOpen()){
        Engine->Tick();
    }
}