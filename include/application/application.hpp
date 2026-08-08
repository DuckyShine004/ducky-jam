#pragma once

#include "application/window.hpp"
#include "engine/engine.hpp"
#include "game/game.hpp"

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
    void validate();

    void run();

  private:
    static inline constexpr int default_width = 2560;
    static inline constexpr int default_height = 1440;

    static inline constexpr const char *title = "Ducky Jam";

    static inline constexpr bool fullscreen = true;

    application::Window m_window;

    std::optional<engine::Engine> m_engine;
    std::optional<game::Game> m_game;

    double m_previous_time;

    static void on_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods);
    static void on_window_resize(GLFWwindow *window, int width, int height);
    static void on_framebuffer_resize(GLFWwindow *window, int width, int height);
    static void on_cursor(GLFWwindow *window, double x, double y);
    static void on_scroll(GLFWwindow *window, double x, double y);
    static void on_drop(GLFWwindow *window, int count, const char **raw_paths);

    void update();
    void render();

    void handle_key_press(GLFWwindow *window, int key, int scanmode, int action, int mods);
    void handle_window_resize(GLFWwindow *window, int width, int height);
    void handle_framebuffer_resize(GLFWwindow *window, int width, int height);
    void handle_cursor(GLFWwindow *window, double x, double y);
    void handle_scroll(GLFWwindow *window, double x, double y);
    void handle_drop(GLFWwindow *window, int count, const char **raw_paths);

    void close();
};

} // namespace application
