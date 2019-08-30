#pragma once
#include <rendering/renderedobject.h>
#include <glm/glm.hpp>
#include <assets/freecamcomponent.h>
#include <components/keyboardeventcomponent.h>
#include <components/mouseeventcomponent.h>
class Madd;
class GameCamera{
public:
  GameCamera();
  ~GameCamera();
  static void HandleEvent(Component* c, int key, int action);
private:
  KeyboardEventComponent mouselockEvent;
  MouseEventComponent mouseMovementEvent;
  KeyboardEventComponent keyboardMovementEvent[6];
  FreecamComponent camera;
};

