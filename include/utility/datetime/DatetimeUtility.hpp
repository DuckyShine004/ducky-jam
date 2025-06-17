#pragma oncee

#include <string>

namespace utility::datetime {

class DatetimeUtility {
  public:
    static std::string getDatetime(const std::string &pattern);
};

} // namespace utility::datetime