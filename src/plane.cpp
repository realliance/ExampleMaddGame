#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "plane.h"
#include <madd.h>
#include <event/keycodes.h>
#include <rendering/renderedobject.h>
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
    planeMesh = RenderedObject::Construct(vertices,"default.vs","default.fs");
    RenderedObject::AddTexture(planeMesh, "base.png");
    // planeMesh.model = glm::translate(planeMesh.model, glm::vec3(0.0f,-1.0f,0.0f));
    RenderedObject::SetTransformation(planeMesh, glm::translate(planeMesh.model, glm::vec3(0.0f,-1.0f,0.0f)));
    Madd::GetInstance().GetSystem("RenderSystem")->Register(&planeMesh);

}

Plane::~Plane(){
    RenderedObject::Destruct(planeMesh);
}

bool Plane::Render(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,-1.0f,0.0f));
    RenderedObject::SetTransformation(planeMesh,model);
    if(!RenderedObject::Render(planeMesh))
        return false;
    return true;
}

bool Plane::ReloadShaders(){
	RenderedObject::ReloadShader(planeMesh);
	return true;
}

bool Plane::Update(){
    //glm::mat4 trans = cubeMesh->GetTransformation();
    //cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(context->GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}
