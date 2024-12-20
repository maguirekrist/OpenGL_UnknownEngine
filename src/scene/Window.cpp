//
//  Window.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/4/22.
//

#include "Window.h"

Window::Window(Camera& camera, int height, int width) : camera(camera), height(height), width(width)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR); //This disables the cursor, which for our engine, we want to enable it by default

    //Initialize custom cursor
    unsigned char pixels[8 * 8 * 4];
    memset(pixels, 0xff, sizeof(pixels));

    GLFWimage image;
    image.width = 8;
    image.height = 8;
    image.pixels = pixels;

    GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);

    glfwSetCursor(glfwWindow, cursor);

    glfwSetWindowUserPointer(glfwWindow, reinterpret_cast<void *>(this));

    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
    glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
    glfwSetScrollCallback(glfwWindow, scroll_callback);
    glfwSetCursorPosCallback(glfwWindow, mouse_callback);
    glfwSetCursorPosCallback(glfwWindow, cursor_move_callback);

    if (glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }

    glfwMakeContextCurrent(glfwWindow);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(glfwWindow);
}

void Window::setPlaceCommand(std::unique_ptr<Command>&& command)
{
    clickCommand = std::move(command);
}

void Window::update()
{
    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
}

void Window::processInput()
{
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //        glfwSetWindowShouldClose(window, true);
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveUp();
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveDown();
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();

    //Debug Views
    if(glfwGetKey(glfwWindow, GLFW_KEY_F1) == GLFW_PRESS)
        debugView = DebugView::None;

    if(glfwGetKey(glfwWindow, GLFW_KEY_F2) == GLFW_PRESS)
        debugView = DebugView::HeightMap;

    if(glfwGetKey(glfwWindow, GLFW_KEY_F3) == GLFW_PRESS)
        debugView = DebugView::HeightMapTexture;
}

void Window::mouse_button_callback(GLFWwindow* p_window, int button, int action, int mods) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        int width, height;

        glfwGetCursorPos(window->glfwWindow, &xpos, &ypos);
        glfwGetWindowSize(window->glfwWindow, &width, &height);

        float y = height - ypos;

        glm::vec3 v0 = glm::unProject(glm::vec3(xpos, y, 0.0f), window->camera.view, window->camera.projection, glm::vec4(0, 0, 800, 600));
        glm::vec3 v1 = glm::unProject(glm::vec3(xpos, y, 1.0f), window->camera.view, window->camera.projection, glm::vec4(0, 0, 800, 600));

        glm::vec3 dir = glm::normalize((v1 - v0));

        glm::mat4 world = glm::mat4(1.0f);
        world = glm::translate(world, window->camera.cameraPos);
        world = glm::scale(world, glm::vec3(window->camera.zoom,  window->camera.zoom, 1.0f));

        glm::vec2 mouseClickPos = glm::vec2(world * glm::vec4(xpos, y, 0, 1));

        std::cout << "MouseClick: " << mouseClickPos.x << " & " << mouseClickPos.y << std::endl;

        window->clickCommand->execute(mouseClickPos);
        //RayCast
        //Cube* result = window->Raycast(dir);
    }
}

static glm::vec2 computeCenter(Window* window) {
    float centerX, centerY;
    centerX = (window->width / 2 ) * window->camera.zoom;
    centerY = (window->height / 2 ) * window->camera.zoom;

    glm::vec2 camCenter = glm::vec2(window->camera.cameraPos.x + centerX, window->camera.cameraPos.y + centerY);
    return camCenter;
}

void Window::scroll_callback(GLFWwindow *p_window, double xoffset, double yoffset) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
    //double cursorX, cursorY;
    //glfwGetCursorPos(window->glfwWindow, &cursorX, &cursorY);
    //window->camera.updateCursorPos(static_cast<int>(cursorX), static_cast<int>(cursorY));

    float centerX, centerY;
    centerX = (window->width / 2.0f) * window->camera.zoom;
    centerY = (window->height / 2.0f) * window->camera.zoom;

    // std::cout << "CamPos: " << window->camera.cameraPos.x << " & " << window->camera.cameraPos.y << std::endl;
    glm::vec2 camCenter = glm::vec2(window->camera.cameraPos.x + centerX, window->camera.cameraPos.y + centerY);

    if(yoffset != 0)
        window->camera.zoom += (yoffset / std::abs(yoffset)) * 0.005f;

    centerX = (window->width / 2 ) * window->camera.zoom;
    centerY = (window->height / 2 ) * window->camera.zoom;

   // std::cout << "CamPos: " << window->camera.cameraPos.x << " & " << window->camera.cameraPos.y << std::endl;

    glm::vec2 camCenterAfter = glm::vec2(window->camera.cameraPos.x + centerX, window->camera.cameraPos.y + centerY);

    glm::vec2 diff = camCenter - camCenterAfter;

    window->camera.cameraPos += glm::vec3(diff, 0.0f);

    //std::cout << "CamCenter: " << camCenter.x << " & " << camCenter.y << std::endl;
}

void Window::cursor_enter_callback(GLFWwindow *window, int entered) {
    if(entered) {

    } else {

    }
}

void Window::cursor_move_callback(GLFWwindow *p_window, double xpos, double ypos) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));

    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, window->camera.cameraPos);
    world = glm::scale(world, glm::vec3(window->camera.zoom,  window->camera.zoom, 1.0f));

    float y = window->height - ypos;

    glm::vec2 mousePosition = glm::vec2(world * glm::vec4(xpos, y, 0, 1));

    window->camera.updateCursorPos(mousePosition.x, mousePosition.y);
}

void Window::mouse_callback(GLFWwindow* p_window, double xPos, double yPos) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
    int width, height;
    glfwGetWindowSize(window->glfwWindow, &width, &height);
    yPos = height - yPos;
}

void Window::framebuffer_size_callback(GLFWwindow* p_window, int width, int height)
{
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));

    window->width = width;
    window->height = height;
    window->camera.updateProjection(width, height);
    glViewport(0, 0, width, height);
}