namespace core::logger {

enum class Severity : int {
    INFO = 0,
    DEBUG = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4,
};

// clang-format off
inline constexpr const char *names[] = {
    "INFO",
    "DEBUG",
    "WARN",
    "ERROR",
    "FATAL",
};

inline constexpr const char *background_colours[] = {
    "#a6e3a1",
    "#89b4fa",
    "#f9e2af",
    "#eba0ac",
    "#f38ba8",
};

inline constexpr const char *text_colours[] = {
    "#11111b",
    "#11111b",
    "#11111b",
    "#11111b",
    "#11111b",
};
// clang-format on

} // namespace core::logger
