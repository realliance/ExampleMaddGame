#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "plane.h"
#include <madd.h>
#include <keycodes.h>
#include <texturesystem.h>
Plane::Plane() {
    float tileScale = 64.0f;
    float planeSize = 25.0f;
    std::vector<float> vertices = {
        planeSize, 0.0f,  planeSize, tileScale, tileScale,
        planeSize, 0.0f, -planeSize, tileScale, 0.0f,
       -planeSize, 0.0f, -planeSize, 0.0f,      0.0f,
       -planeSize, 0.0f,  planeSize, 0.0f,      tileScale,
       -planeSize, 0.0f, -planeSize, 0.0f,      0.0f,
        planeSize, 0.0f,  planeSize, tileScale, tileScale,
    };
    tex.filename = "base.png";
    Madd::GetInstance().GetSystem("TextureSystem")->Register(&tex);

    mesh.vertices = vertices;
    Madd::GetInstance().GetSystem("MeshSystem")->Register(&mesh);

    shader.fragmentShaderPath = "default.fs";
    shader.vertexShaderPath = "default.vs";
    Madd::GetInstance().GetSystem("ShaderSystem")->Register(&shader);


    renderedPlane = RenderedComponent{};
    renderedPlane.texture = &tex;
    renderedPlane.mesh = &mesh;
    renderedPlane.shader = &shader;
    renderedPlane.model = glm::mat4(1.f);
    renderedPlane.model = glm::translate(renderedPlane.model, glm::vec3(0.0f,-1.0f,0.0f));
    renderedPlane.shade = glm::vec4(1.f);
    
    Madd::GetInstance().GetSystem("RenderSystem")->Register(&renderedPlane);

}

Plane::~Plane(){
    Madd::GetInstance().GetSystem("TextureSystem")->Unregister(&tex);
    Madd::GetInstance().GetSystem("MeshSystem")->Unregister(&mesh);
    Madd::GetInstance().GetSystem("ShaderSystem")->Unregister(&shader);
    Madd::GetInstance().GetSystem("RenderSystem")->Unregister(&renderedPlane);
}