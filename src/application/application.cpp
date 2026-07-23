#include <GLFW/glfw3.h>

#include "external/glad/glad.h"

#include "application/application.hpp"

#include "engine/engine.hpp"
#include "engine/sound/sound_manager.hpp"
#include "engine/graphic/shader/shader_manager.hpp"
#include "engine/graphic/effect/effect_manager.hpp"
#include "engine/graphic/texture/texture_manager.hpp"

#include "game/skinning/skin_manager.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine;
using namespace engine::sound;
using namespace engine::graphic::shader;
using namespace engine::graphic::effect;
using namespace engine::graphic::texture;

using namespace game::skinning;

namespace application {

Application::Application() : m_last_time(0.0) {
}

Application::~Application() {
    this->on_cleanup();
}

bool Application::initialise() {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialise GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow *window = glfwCreateWindow(2560, 1440, "Duck Jam", nullptr, nullptr);

    if (window == nullptr) {
        LOG_ERROR("Failed to create window");
        this->on_cleanup();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialise GLAD");
        this->on_cleanup();
        return false;
    }

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, Application::on_key_press);
    glfwSetFramebufferSizeCallback(window, Application::on_window_resize);
    glfwSetCursorPosCallback(window, Application::on_cursor);
    glfwSetScrollCallback(window, Application::on_scroll);

    m_window = window;

    return true;
}

void Application::load() {
    int width;
    int height;

    glfwGetFramebufferSize(m_window, &width, &height);

    glViewport(0, 0, width, height);

    SoundManager::get_instance().initialise();
    ShaderManager::get_instance().initialise();
    TextureManager::get_instance().initialise();
    SkinManager::get_instance().initialise();

    /* NOTE: MUST BE LOADED AFTER SHADERS ARE LOADED */
    EffectManager::get_instance().initialise();

    m_engine.initialise();
}

void Application::run() {
    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(m_window)) {
        this->update(m_engine);
        this->render(m_engine);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Application::update(Engine &engine) {
    double time = glfwGetTime();
    double delta_time = time - m_last_time;

    m_last_time = time;

    engine.update(m_window, delta_time);
}

void Application::render(Engine &engine) {
    const float R = 0.0f;
    const float G = 0.0f;
    const float B = 0.0f;

    glClearColor(R, G, B, 0.0f);

    engine.render();
}

void Application::on_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_key_press(window, key, scanmode, action, mods);
}

void Application::handle_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        int cursor_mode = glfwGetInputMode(m_window, GLFW_CURSOR);

        if (cursor_mode == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void Application::on_window_resize(GLFWwindow *window, int width, int height) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_window_resize(window, width, height);
}

void Application::handle_window_resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::on_cursor(GLFWwindow *window, double x, double y) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_cursor(window, x, y);
}

void Application::handle_cursor(GLFWwindow *window, double x, double y) {
}

void Application::on_scroll(GLFWwindow *window, double x, double y) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_scroll(window, x, y);
}

void Application::handle_scroll(GLFWwindow *window, double x, double y) {
}

void Application::on_cleanup() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

} // namespace application
