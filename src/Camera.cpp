//
//  Camera.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 5/31/22.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 defaultPos) {
    cameraPos = defaultPos;
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    view = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), cameraUp);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::moveForward() {
    cameraPos += cameraSpeed * cameraFront;
}

void Camera::moveBackward() {
    cameraPos -= cameraSpeed * cameraFront;
}

void Camera::moveLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::updateCamView() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::circleAround(float time) {
    const float radius = 10.0f;
    float camX = sin(time) * radius;
    float camZ = cos(time) * radius;
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::updateCamSpeed(float dt) {
    cameraSpeed = 2.5f * dt;
}

