#pragma once
#include <components/renderedcomponent.h>
#include <components/meshcollidercomponent.h>
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Cube{
    public:
        Cube();
        ~Cube();
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        RenderedComponent cubeMesh;
        MeshColliderComponent colliderA;
        MeshColliderComponent colliderB;
        std::vector<glm::vec3> cubePositions;
		int textures[2];
};

