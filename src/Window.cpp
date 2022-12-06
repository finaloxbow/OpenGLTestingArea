#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* windowName)
: m_width(width), m_height(height) {
    if (!glfwInit()) {
        throw "GLFW init failed.";
    }

    m_windowPtr = glfwCreateWindow(m_width, m_height, windowName, NULL, NULL);
    if (m_windowPtr == NULL)
        throw "Window creation failed.";

    //glfwSetWindowPos(m_windowPtr, (m_maxWidth / 2) - (m_width / 2), (m_maxHeight / 2) - (m_height / 2));
    glfwSwapInterval(0);
    glfwMakeContextCurrent(m_windowPtr);
}

Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* Window::getWindowPtr()
{
    return m_windowPtr;
}

unsigned int Window::getWidth()
{
    return m_width;
}

unsigned int Window::getHeight()
{
    return m_height;
}

void Window::frameUpdate()
{
    processInput();
    glfwPollEvents();
}

void Window::processInput()
{
    if (glfwGetKey(m_windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_windowPtr, true);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //TODO: resize buffer
    glViewport(0,0, width, height);

}
