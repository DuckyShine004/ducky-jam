namespace logger {

enum class Severity : int {
    INFO = 0,
    DEBUG,
    WARN,
    ERROR,
    FATAL,
};

// clang-format off
inline static constexpr const char *_NAMES[] = {
    "INFO",
    "DEBUG",
    "WARN",
    "ERROR",
    "FATAL",
};

inline static constexpr const char *_BACKGROUND_COLOURS[] = {
    "\033[42m",
    "\033[46m",
    "\033[43m",
    "\033[41m",
    "\033[45m",
};

inline static constexpr const char *_TEXT_COLOURS[] = {
    "\033[30m",
    "\033[30m",
    "\033[30m",
    "\033[97m",
    "\033[97m",
};
// clang-format on

} // namespace logger