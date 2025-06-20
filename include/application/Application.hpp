#pragma once

#include <GLFW/glfw3.h>

namespace application {

class Application {
  public:
    Application();

    void initialise();

    void load();

    void run();

  private:
    GLFWwindow *_window;

    float _lastTime;

    void update();

    void render();

    void setWindowSize(int width, int height);

    void onResize(GLFWwindow *window, int width, int height);
};

} // namespace application