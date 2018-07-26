#ifndef PLANE_H
#define PLANE_H
#include "gameobject.h"
#include "renderedobject.h"
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Plane : public GameObject{
    public:
        Plane(Madd* context);
        ~Plane();
        Madd* GetContext(){return context;};
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        RenderedObject* planeMesh;
        Madd* context;
};

#endif //CUBE_H