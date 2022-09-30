//
//  Camera.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 5/31/22.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 defaultPos, int width, int height) {
    cameraPos = defaultPos;
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //view = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), cameraUp);
    //projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f); //we may use projection later on, so keep this in mind

    view = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
}

void Camera::moveForward() {
    cameraPos += cameraSpeed * cameraFront;
}

void Camera::moveBackward() {
    cameraPos -= cameraSpeed * cameraFront;
}

void Camera::moveUp() {
    cameraPos += cameraSpeed * cameraUp;
}

void Camera::moveDown() {
    cameraPos -= cameraSpeed * cameraUp;
}

void Camera::moveLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::updateCamView() {
    view = glm::mat4(1.0f);
    view = glm::translate(view, cameraPos);
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
}

void Camera::updateProjection(int width, int height) {
    projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
}

void Camera::updateCursorPos(int x, int y) {
    cursorPos = glm::vec2(x, y);
}


void Camera::updateCamSpeed(float dt) {
    cameraSpeed = 10.0f * dt;
}

