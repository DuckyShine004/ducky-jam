#pragma once

#include <vector>

namespace utility::datatype {

class CopyUtility {
  public:
    static std::vector<float> convertToVectorFloat1D(const float array[]);
};

} // namespace utility::datatype