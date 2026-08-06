#include "application/application.hpp"

#include "core/logger/logger_macros.hpp"
#include "engine/engine.hpp"

#include "external/glad/glad.h"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

using namespace engine;

namespace application {

Application::Application() : m_last_time(0.0), m_is_mouse_captured(false) {
}

Application::~Application() {
    close();
}

bool Application::initialise() {
    if (!m_window.create(m_DEFAULT_WIDTH, m_DEFAULT_HEIGHT, m_TITLE, m_FULLSCREEN)) {
        return false;
    }

    m_engine.emplace(m_window.physical_resolution().w, m_window.physical_resolution().h);

    GLFWwindow *window = m_window.window();

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, Application::on_key_press);
    glfwSetWindowSizeCallback(window, Application::on_window_resize);
    glfwSetFramebufferSizeCallback(window, Application::on_framebuffer_resize);
    glfwSetCursorPosCallback(window, Application::on_cursor);
    glfwSetScrollCallback(window, Application::on_scroll);
    glfwSetDropCallback(window, Application::on_drop);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    return true;
}

void Application::load() {
    // AudioManager::get_instance().initialise();
    // ShaderManager::get_instance().initialise();
    // TextureManager::get_instance().initialise();
    // SkinManager::get_instance().initialise();

    /* NOTE: MUST BE LOADED AFTER SHADERS ARE LOADED */
    // EffectManager::get_instance().initialise();
}

void Application::run() {
    if (!m_engine.has_value()) {
        throw std::runtime_error("For some reason the engine was never initialised...");
    }

    glfwSwapInterval(0);

    while (!m_window.should_close()) {
        this->update();
        this->render();

        m_window.swap_buffers();
        m_window.poll_events();
    }
}

void Application::update() {
    double time = glfwGetTime();
    double delta_time = time - m_last_time;

    m_last_time = time;

    m_engine->update(delta_time);
}

void Application::render() {
    const float R = 0.0f;
    const float G = 0.0f;
    const float B = 0.0f;

    glClearColor(R, G, B, 0.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    m_engine->render();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        int cursor_mode = glfwGetInputMode(window, GLFW_CURSOR);

        if (cursor_mode == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void Application::on_window_resize(GLFWwindow *window, int width, int height) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_window_resize(window, width, height);
}

void Application::handle_window_resize(GLFWwindow *window, int width, int height) {
    m_window.resize_logical(width, height);
    m_engine->resize(width, height);
}

void Application::on_framebuffer_resize(GLFWwindow *window, int width, int height) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_framebuffer_resize(window, width, height);
}

void Application::handle_framebuffer_resize(GLFWwindow *window, int width, int height) {
    m_window.resize_physical(width, height);
    m_engine->resize(width, height);
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

void Application::on_drop(GLFWwindow *window, int count, const char **paths) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_drop(window, count, paths);
}

void Application::handle_drop(GLFWwindow *window, int count, const char **paths) {
    std::vector<std::string> string_paths(count);

    for (int i = 0; i < count; ++i) {
        string_paths[i] = paths[i];
    }

    m_engine->drop(string_paths);
}

void Application::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace application
