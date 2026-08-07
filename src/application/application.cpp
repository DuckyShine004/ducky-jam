#include "application/application.hpp"

#include "core/exceptions/runtime_exception.hpp"
#include "core/platform/environment.hpp"
#include "core/utility/file_utility.hpp"
#include "engine/engine.hpp"

#include "external/glad/glad.h"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <filesystem>

namespace application {

namespace exceptions = core::exceptions;

Application::Application() : m_previous_time(0.0) {
}

Application::~Application() {
    close();
}

bool Application::initialise() {
    if (!m_window.create(default_width, default_height, title, fullscreen)) {
        return false;
    }

    m_engine.emplace(m_window.physical_resolution().w, m_window.physical_resolution().h);
    m_game.emplace(m_engine->services());

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    return true;
}

void Application::load() {
    const std::filesystem::path app_data_path = core::platform::app_data_path();

    core::utility::FileUtility::create_directory(app_data_path);

    m_engine->load();
}

void Application::validate() {
    if (!m_engine.has_value()) {
        throw exceptions::RuntimeException("For some reason the engine was never initialised. Did you perhaps forget to invoke application.initialise()?");
    }

    if (!m_game.has_value()) {
        throw exceptions::RuntimeException("For some reason the game was never initialised. Did you perhaps forget to invoke application.initialise()?");
    }

    if (!core::utility::FileUtility::exists(core::platform::app_data_path())) {
        throw exceptions::RuntimeException("Application data path was never initialised.");
    }
}

void Application::run() {
    validate();

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
    double delta_time = time - m_previous_time;

    m_previous_time = time;

    m_game->update(delta_time);
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_game->render();

    // IMGUI rendering
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_game->render_imgui();

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
    // m_engine->resize(width, height);
}

void Application::on_framebuffer_resize(GLFWwindow *window, int width, int height) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_framebuffer_resize(window, width, height);
}

void Application::handle_framebuffer_resize(GLFWwindow *window, int width, int height) {
    m_window.resize_physical(width, height);
    // m_engine->resize(width, height);
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

void Application::on_drop(GLFWwindow *window, int count, const char **raw_paths) {
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));
    application->handle_drop(window, count, raw_paths);
}

void Application::handle_drop(GLFWwindow *window, int count, const char **raw_paths) {
    std::vector<std::filesystem::path> paths(count);

    for (int i = 0; i < count; ++i) {
        paths[i] = raw_paths[i];
    }

    m_game->import(paths);
}

void Application::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace application
