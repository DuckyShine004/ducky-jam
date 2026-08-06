#include "application/window.hpp"

#include "core/logger/logger_macros.hpp"

#include "external/glad/glad.h"

#include <GLFW/glfw3.h>

namespace application {

Window::Window() : m_fullscreen(false), m_window(nullptr) {
}

Window::~Window() {
    destroy();
}

bool Window::create(int width, int height, const std::string &title, bool fullscreen) {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialise GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWmonitor *monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    if (fullscreen) {
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    }

    m_window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);

    if (m_window == nullptr) {
        LOG_ERROR("Failed to create window");
        destroy();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    glfwGetWindowSize(m_window, &m_logical_resolution.w, &m_logical_resolution.h);
    glfwGetFramebufferSize(m_window, &m_physical_resolution.w, &m_physical_resolution.h);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialise GLAD");
        destroy();
        return false;
    }

    resize_physical(m_physical_resolution.w, m_physical_resolution.h);

    m_fullscreen = fullscreen;

    return true;
}

void Window::resize_logical(int width, int height) {
    m_logical_resolution.w = width;
    m_logical_resolution.h = height;
}

void Window::resize_physical(int width, int height) {
    m_physical_resolution.w = width;
    m_physical_resolution.h = height;

    glViewport(0, 0, width, height);
}

bool Window::should_close() {
    return glfwWindowShouldClose(m_window);
}

void Window::swap_buffers() {
    glfwSwapBuffers(m_window);
}

void Window::poll_events() {
    glfwPollEvents();
}

void Window::destroy() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

GLFWwindow *Window::window() {
    return m_window;
}

const core::structs::Vector2<int> &Window::logical_resolution() const {
    return m_logical_resolution;
}

const core::structs::Vector2<int> &Window::physical_resolution() const {
    return m_physical_resolution;
}

} // namespace application
