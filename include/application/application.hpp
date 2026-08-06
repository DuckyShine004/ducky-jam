#pragma once

#include "application/window.hpp"
#include "engine/engine.hpp"

#include <GLFW/glfw3.h>

#include <optional>

namespace application {

class Application {
  public:
    Application();
    ~Application();

    Application(const Application &other) = delete;
    Application &operator=(const Application &other) = delete;
    Application(Application &&other) = delete;
    Application &operator=(Application &&other) = delete;

    bool initialise();
    void load();
    void run();

  private:
    static inline constexpr int m_DEFAULT_WIDTH = 2560;
    static inline constexpr int m_DEFAULT_HEIGHT = 1440;

    static inline constexpr const char *m_TITLE = "Ducky Jam";

    static inline constexpr bool m_FULLSCREEN = true;

    application::Window m_window;

    std::optional<engine::Engine> m_engine;

    double m_last_time;

    bool m_is_mouse_captured;

    static void on_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods);
    static void on_window_resize(GLFWwindow *window, int width, int height);
    static void on_framebuffer_resize(GLFWwindow *window, int width, int height);
    static void on_cursor(GLFWwindow *window, double x, double y);
    static void on_scroll(GLFWwindow *window, double x, double y);
    static void on_drop(GLFWwindow *window, int count, const char **paths);

    void update();
    void render();

    void handle_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods);
    void handle_window_resize(GLFWwindow *window, int width, int height);
    void handle_framebuffer_resize(GLFWwindow *window, int width, int height);
    void handle_cursor(GLFWwindow *window, double x, double y);
    void handle_scroll(GLFWwindow *window, double x, double y);
    void handle_drop(GLFWwindow *window, int count, const char **paths);

    void close();
};

} // namespace application
