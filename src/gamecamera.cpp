#include <glm/gtc/matrix_transform.hpp>
#include <gamecamera.h>
#include <madd.h>
#include <assets/freecam.h>
#include <event/eventhandler.h>

GameCamera::GameCamera() {
    cameraObj = new FreeCam();
    Madd::GetInstance().SetMainCamera(cameraObj); 
}

GameCamera::~GameCamera(){
   delete cameraObj;
   Madd::GetInstance().SetMainCamera(nullptr);
}

bool GameCamera::Update(){
    cameraObj->Update();
    return true;
}

bool GameCamera::ReloadShaders(){return true;}
bool GameCamera::Render(){return true;}
