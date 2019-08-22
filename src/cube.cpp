#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include <madd.h>
#include <event/eventhandler.h>
#include <physics/collider.h>
#include <algorithm>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
Cube::Cube() {
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    cubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -1.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -2.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -3.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3( 0.0f,  0.0f,  1.4f)
    };
    cubeMesh = new RenderedObject(this);
    cubeMesh->RenderInit(vertices,"default.vs","default.fs");
    textures[0]=cubeMesh->AddTexture("container.jpg");
	textures[1]=cubeMesh->AddTexture("logo.png");
}

Cube::~Cube(){
    delete cubeMesh;
}

glm::mat4 getModel(int i, const glm::vec3& pos){
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 offset = glm::vec3(3.0f,3.0f,3.0f);
    model = glm::translate(model, pos+offset);//+glm::vec3(glm::sin(Madd::GetInstance().GetTime()+i*20.f)/10.f,0.f,0.f));
    float angle = Madd::GetInstance().GetTime()/10.f + glm::radians(i*20.0f);
    glm::vec3 axis = glm::vec3(1.0f, 0.3f, 0.5f);
    model = glm::rotate(model, angle, axis);
    return model;
}

bool Cube::Render(){
    std::vector<glm::vec3> collisionMesh = {
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f)
    };
    Collider a(collisionMesh);
    a.updateModel(getModel(cubePositions.size()-1,cubePositions.back()));
    Collider b(collisionMesh);
    b.updateModel(getModel(0,cubePositions.front()));
    bool collides = b.Collides(a);
    
    for(int i = 0; i < cubePositions.size(); i++){
		cubeMesh->SetTexture(textures[i % 2]);
        glm::mat4 model = getModel(i,cubePositions[i]);
        cubeMesh->SetTransformation(model);
        if( collides && (i == 0 || i == cubePositions.size()-1)){
            cubeMesh->SetShade({1.0f,0.75f,0.5f,1.0f});
        }else{
            cubeMesh->SetShade(glm::vec4(1.0f));
        }
        if(!cubeMesh->Render())
            return false;
    }
    cubeMesh->SetTransformation(glm::mat4(1.0f));
    return true;
}

bool Cube::ReloadShaders(){
	cubeMesh->LoadShader();
	return true;
}

bool Cube::Update(){
    //glm::mat4 trans = cubeMesh->GetTransformation();
    //cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(Madd::GetInstance().GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}
