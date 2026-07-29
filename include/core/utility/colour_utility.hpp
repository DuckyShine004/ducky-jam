#pragma once

#include <glm/glm.hpp>

#include <array>
#include <string>

#include "core/structs/vector4.hpp"

namespace core::utility {

class ColourUtility {
  public:
    static std::string get_ansi_foreground_from_hex(const std::string &hex);
    static std::string get_ansi_background_from_hex(const std::string &hex);
    static glm::vec3 get_high_precision_RGB(const float (&array)[3]);
    static core::structs::Vector4<std::uint8_t> hex_to_rgba(const std::string &hex);

  private:
    static std::array<int, 3> get_RGB_from_hex(const std::string &hex);
};

} // namespace core::utility
