#pragma once

#include <GLFW/glfw3.h>

namespace application {

class Application {
  public:
    Application();

    void initialise();

    void run();

  private:
    GLFWwindow *_window;

    float _lastTime;

    void update();

    void render();

    static void onResize(GLFWwindow *window, int width, int height);
};

} // namespace application