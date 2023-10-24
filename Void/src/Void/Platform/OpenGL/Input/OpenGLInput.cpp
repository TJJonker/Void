#include "pch.h"
#include "OpenGLInput.h"

namespace Void {

    OpenGLInput::OpenGLInput(void* window)
    {
        m_Window = static_cast<GLFWwindow*>(window);
    }

    // TODO: Rework this function, does not work properly.
    bool OpenGLInput::VKeyPressed(int keycode)
    {
        int keyState = glfwGetKey(m_Window, keycode);
        return keyState == GLFW_PRESS && keyState != GLFW_REPEAT; 
    }

    bool OpenGLInput::VKeyDown(int keycode)
    {
        int keyState = glfwGetKey(m_Window, keycode);
        return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
    }

    // TODO: Rework this function, does not work properly.
    bool OpenGLInput::VMousePressed(int button)
    {
        int mouseState = glfwGetMouseButton(m_Window, button);
        return mouseState == GLFW_PRESS;
    }

    glm::vec2 OpenGLInput::VMousePosition()
    {
        double x, y; 
        glfwGetCursorPos(m_Window, &x, &y); 
        return { x, y }; 
    }
}