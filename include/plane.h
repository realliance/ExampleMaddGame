#pragma once
#include <components/renderedcomponent.h>
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Plane{
    public:
        Plane();
        ~Plane();
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        RenderedComponent planeMesh;
};

