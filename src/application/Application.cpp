#include <external/glad/glad.h>

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"

#include <application/Application.hpp>

#include <manager/SceneManager.hpp>

#include <application/game/singleplayer/play/Play.hpp>

#include <configuration/Configuration.hpp>

#include <configuration/display/DisplayConfiguration.hpp>

#include <logger/LoggerMacros.hpp>

#include <iostream>

using namespace manager;

using namespace configuration;

using namespace configuration::display;

using namespace application::game::singleplayer::play;

namespace application {

Application::Application() : _lastTime(0.0f), _framesPerSecond(0.0f) {
}

void Application::initialise() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Ducky Jam", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;

        return;
    }

    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

        application->onResize(window, width, height);
    });

    this->_window = window;

    // Initialise IMGUI after gl
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::load() {
    SceneManager::getInstance().setScene(std::make_unique<Play>());

    DisplayConfiguration &displayConfiguration = DisplayConfiguration::getInstance();

    displayConfiguration.load(".config/display.conf");

    int width;
    int height;

    glfwGetFramebufferSize(this->_window, &width, &height);

    this->setWindowSize(width, height);
}

void Application::run() {
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(this->_window)) {
        this->update();

        this->render();

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void Application::update() {
    float time = glfwGetTime();

    float deltaTime = time - this->_lastTime;

    Scene &scene = SceneManager::getInstance().getScene();

    scene.update(deltaTime);
}

void Application::render() {
    Scene &scene = SceneManager::getInstance().getScene();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    scene.render();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(50, 50, 50, 200));
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::Begin("##fps_overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
    ImGui::TextColored(ImVec4(1, 1, 1, 1), "FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::onResize(GLFWwindow *window, int width, int height) {
    this->setWindowSize(width, height);
}

void Application::setWindowSize(int width, int height) {
    Scene &scene = SceneManager::getInstance().getScene();

    glViewport(0, 0, width, height);

    DisplayConfiguration::getInstance().updateResolution(width, height);

    scene.updateProjectionMatrix(width, height);
}

} // namespace application