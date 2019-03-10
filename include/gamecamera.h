#ifndef GAMECAMERA_H
#define GAMECAMERA_H
#include "gameobject.h"
#include "renderedobject.h"
#include <glm/glm.hpp>
class Camera;
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
        Camera* cameraObj;
        RenderedObject* cubeMesh;
        glm::vec3 position;
};

#endif //GAMECAMERA_H