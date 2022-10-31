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

    glm::vec2 cursorPos;

    float zoom = 1/32.0f;

    int view_width;
    int view_height;
    
    Camera(glm::vec3 defaultPos, int width, int height);


    void moveForward();
    void moveBackward();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void updateCamSpeed(float dt);
    
    void updateCamView();
    void updateProjection(int width, int height);
    void updateCursorPos(int x, int y);
private:
    glm::vec3 cameraTarget;
    glm::vec3 up;
    glm::vec3 cameraRight;
    
    
    float cameraSpeed = 5.0f;
};

#endif /* Camera_hpp */
