#pragma once
#include <glm/glm.hpp>
#include <components/freecamcomponent.h>
#include <components/keyboardeventcomponent.h>
#include <components/mouseeventcomponent.h>
class Madd;
class KeyboardEventSystem;
class MouseEventSystem;
class GameCamera{
public:
  GameCamera();
  void Unregister();
  static void HandleEvent(Component* c, WindowComponent* window, int key, int action);
  FreecamComponent camera;
private:
  KeyboardEventComponent mouselockEvent;
  MouseEventComponent mouseMovementEvent;
  KeyboardEventComponent keyboardMovementEvent[7];
  KeyboardEventSystem* keyboardeventsys;
  MouseEventSystem* mouseeventsys;
};

