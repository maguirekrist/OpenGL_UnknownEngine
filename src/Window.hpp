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

class Window {
public: 
    Window(Camera& camera);
    ~Window();

    Camera& camera;
       
    int height;
    int width;
    
    //Cube* Raycast(glm::vec3 ray);
    void processInput();
    void update();
    bool isOpen();
    //void loadSceneItems(std::vector<Cube>& cubes);
    
private:
    GLFWwindow* glfwWindow;
    bool isFirstMouse = true;

    //events
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* Window_hpp */
