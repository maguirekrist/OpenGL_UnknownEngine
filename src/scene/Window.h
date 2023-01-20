//
//  Window.hpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/4/22.
//

#ifndef Window_hpp
#define Window_hpp

#include <gl/glew.h>
#include <stdio.h>
#include <vector>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <cstring>
#include <memory>
#include "../Command.h"

enum DebugView {
    None,
    HeightMap,
    HeightMapTexture
};

class Window {
public: 
    Window(Camera& camera, int width, int height);
    ~Window();

    Camera& camera;
    DebugView debugView = DebugView::None;
    std::unique_ptr<Command> clickCommand;


    int height;
    int width;
    
    //Cube* Raycast(glm::vec3 ray);
    void processInput();
    void update();
    bool isOpen();
    void setPlaceCommand(std::unique_ptr<Command>&& command);
   

private:
    GLFWwindow* glfwWindow;

    //events
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void cursor_move_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif /* Window_hpp */
