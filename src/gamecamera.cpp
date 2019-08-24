#include <glm/gtc/matrix_transform.hpp>
#include <gamecamera.h>
#include <madd.h>
#include <assets/freecam.h>
#include <event/eventhandler.h>
#include <event/keyboardeventsystem.h>
#include <event/mouseeventsystem.h>

GameCamera::GameCamera() {
    cameraObj = FreeCam::Construct();

    mouseMovementEvent = MouseEventComponent{};
    mouseMovementEvent.callback = [this](Component* c, double a, double b) {FreeCam::ProcessCursorPos(cameraObj,a,b);};
    MouseEventSystem::GetInstance().Register(&mouseMovementEvent);

    mouselockEvent = KeyboardEventComponent{};
    mouselockEvent.c = &cameraObj;
    mouselockEvent.callback = [this](Component* c, int a, int b) { FreeCam::ToggleMouseLock(cameraObj, a,b); };
    mouselockEvent.code = KEY_TAB;
    KeyboardEventSystem::GetInstance().Register(&mouselockEvent);
    Madd::GetInstance().SetMainCamera(&cameraObj.camera);
}

GameCamera::~GameCamera(){
   FreeCam::Destruct(cameraObj);
   Madd::GetInstance().SetMainCamera(nullptr);
}

bool GameCamera::Update(){
    FreeCam::Update(cameraObj);
    return true;
}

bool GameCamera::ReloadShaders(){return true;}
bool GameCamera::Render(){return true;}
