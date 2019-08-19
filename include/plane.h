#ifndef PLANE_H
#define PLANE_H
#include "gameobject.h"
#include "graphics/renderedobject.h"
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Plane : public GameObject{
    public:
        Plane();
        ~Plane();
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        RenderedObject* planeMesh;
};

#endif //CUBE_H
