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

    void update();

    void render();
};

} // namespace application