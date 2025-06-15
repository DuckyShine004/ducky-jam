#include <external/glad/glad.h>

#include <application/Application.hpp>

#include <manager/SceneManager.hpp>

#include <application/game/singleplayer/play/Play.hpp>

#include <iostream>

using namespace manager;

using namespace application::game::singleplayer::play;

namespace application {

Application::Application() = default;

void Application::initialise() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1080, 720, "Ducky Jam", nullptr, nullptr);

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

    this->_window = window;

    SceneManager::getInstance().setScene(std::make_unique<Play>());
}

void Application::run() {
    while (!glfwWindowShouldClose(this->_window)) {
        this->update();

        this->render();

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::update() {
}

void Application::render() {
    Scene &scene = SceneManager::getInstance().getScene();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.render();
}

} // namespace application