#ifndef GAMECAMERA_H
#define GAMECAMERA_H
#include <gameobject.h>
#include <rendering/renderedobject.h>
#include <glm/glm.hpp>
#include <assets/freecamcomponent.h>
#include <components/keyboardeventcomponent.h>
#include <components/mouseeventcomponent.h>
class Madd;
class GameCamera : public GameObject{
public:
  GameCamera();
  ~GameCamera();
  bool Render();
  bool Update();
  bool ReloadShaders();
  void ProcessInput(int key, int action);
private:
  KeyboardEventComponent mouselockEvent;
  MouseEventComponent mouseMovementEvent;
  FreecamComponent cameraObj;
  RenderedObject* cubeMesh;
  glm::vec3 position;
};

#endif //GAMECAMERA_H
