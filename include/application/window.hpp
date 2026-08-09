#pragma once

#include "core/structs/vector2.hpp"

#include <GLFW/glfw3.h>

#include <string>

namespace application {

class Window {
  public:
    Window();
    ~Window();

    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;
    Window(Window &&other) = delete;
    Window &operator=(Window &&other) = delete;

    bool create(int width, int height, const std::string &title, bool fullscreen);
    void resize_logical(int width, int height);
    void resize_framebuffer(int width, int height);
    bool should_close();
    void swap_buffers();
    void poll_events();
    void destroy();

    GLFWwindow *window();

    const core::structs::Vector2<int> &logical_resolution() const;
    const core::structs::Vector2<int> &framebuffer_resolution() const;

  private:
    bool m_fullscreen;

    GLFWwindow *m_window;

    core::structs::Vector2<int> m_logical_resolution;
    core::structs::Vector2<int> m_framebuffer_resolution;
};

} // namespace application
