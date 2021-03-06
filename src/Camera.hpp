//
//  Camera.hpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 5/31/22.
//
#pragma once
#ifndef Camera_hpp
#define Camera_hpp
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 cameraDirection;
    glm::vec3 cameraPos;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;
    
    glm::mat4 view;
    glm::mat4 projection;
        
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 400;
    float lastY = 300;
    
    Camera(glm::vec3 defaultPos);
    
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void updateCamSpeed(float dt);
    
    void updateCamView();
    void circleAround(float time);
    
private:
    glm::vec3 cameraTarget;
    glm::vec3 up;
    glm::vec3 cameraRight;
    
    
    float cameraSpeed = 5.0f;
};

#endif /* Camera_hpp */
