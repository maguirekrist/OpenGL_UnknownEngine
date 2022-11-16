//
//  Window.hpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/4/22.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <vector>
#include "Cube.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <functional>

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

    std::vector<std::function<void(glm::vec2, bool)>> events;

    int height;
    int width;
    
    //Cube* Raycast(glm::vec3 ray);
    void processInput();
    void update();
    bool isOpen();


private:
    GLFWwindow* glfwWindow;

    //events
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
};

#endif /* Window_hpp */
