#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "plane.h"
#include "madd.h"
#include "eventhandler.h"
Plane::Plane(Madd* context):context(context){
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
    planeMesh = new RenderedObject(this);
    planeMesh->RenderInit(vertices,"default.vs","default.fs","base.png");
}

Plane::~Plane(){
    delete planeMesh;
}

bool Plane::Render(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,-1.0f,0.0f));
    planeMesh->SetTransformation(model);
    if(!planeMesh->Render())
        return false;
    return true;
}

bool Plane::ReloadShaders(){
	planeMesh->LoadShader();
	return true;
}

bool Plane::Update(){
    //glm::mat4 trans = cubeMesh->GetTransformation();
    //cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(context->GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}