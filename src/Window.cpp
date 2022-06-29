//
//  Window.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/4/22.
//

#include "Window.hpp"

Window::Window(Camera& camera) : camera(camera)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(glfwWindow, reinterpret_cast<void *>(this));

    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
    glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
    glfwSetCursorPosCallback(glfwWindow, mouse_callback);

    if (glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }

    glfwMakeContextCurrent(glfwWindow);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
}

void Window::loadSceneItems(std::vector<Cube>& cubes)
{
    this->cubes = &cubes;
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(glfwWindow);
}

void Window::update()
{
    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
}

Cube* Window::Raycast(glm::vec3 ray) {
    Cube* hitCube = nullptr;

    for (auto& cube : *cubes) {
        float t1 = (cube.bounds.min.x - camera.cameraPos.x) / ray.x;
        float t2 = (cube.bounds.max.x - camera.cameraPos.x) / ray.x;

        float t3 = (cube.bounds.min.y - camera.cameraPos.y) / ray.y;
        float t4 = (cube.bounds.max.y - camera.cameraPos.y) / ray.y;

        float t5 = (cube.bounds.min.z - camera.cameraPos.z) / ray.z;
        float t6 = (cube.bounds.max.z - camera.cameraPos.z) / ray.z;

        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        if (!(tmax < 0) && !(tmin > tmax)) {
            cube.color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
            std::cout << "Cube hit with" << cube.color.r << std::endl;
            hitCube = &cube;
            break;
        }
    }

    return hitCube;
}

void Window::processInput()
{
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //        glfwSetWindowShouldClose(window, true);
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward();
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward();
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
}

void Window::mouse_button_callback(GLFWwindow* p_window, int button, int action, int mods) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        int width, height;

        glfwGetCursorPos(window->glfwWindow, &xpos, &ypos);
        glfwGetWindowSize(window->glfwWindow, &width, &height);

        float y = height - ypos;
        std::cout << y << " vs. " << ypos << std::endl;
        glm::vec3 v0 = glm::unProject(glm::vec3(xpos, y, 0.0f), window->camera.view, window->camera.projection, glm::vec4(0, 0, 800, 600));
        glm::vec3 v1 = glm::unProject(glm::vec3(xpos, y, 1.0f), window->camera.view, window->camera.projection, glm::vec4(0, 0, 800, 600));

        glm::vec3 dir = glm::normalize((v1 - v0));

        Cube* result = window->Raycast(dir);
    }
}


void Window::mouse_callback(GLFWwindow* p_window, double xPos, double yPos) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
    if (window->isFirstMouse)
    {
        window->camera.lastX = xPos;
        window->camera.lastY = yPos;
        window->isFirstMouse = false;
    }

    float xoffset = xPos - window->camera.lastX;
    float yoffset = window->camera.lastY - yPos;
    window->camera.lastX = xPos;
    window->camera.lastY = yPos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    window->camera.yaw += xoffset;
    window->camera.pitch += yoffset;

    //Clamp pitch
    if (window->camera.pitch > 89.0f) {
        window->camera.pitch = 89.0f;
    }
    if (window->camera.pitch < -89.0f) {
        window->camera.pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(window->camera.yaw)) * cos(glm::radians(window->camera.pitch));
    direction.y = sin(glm::radians(window->camera.pitch));
    direction.z = sin(glm::radians(window->camera.yaw)) * cos(glm::radians(window->camera.pitch));
    window->camera.cameraFront = glm::normalize(direction);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}