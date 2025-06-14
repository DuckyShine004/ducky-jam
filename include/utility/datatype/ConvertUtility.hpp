#pragma once

#include <vector>

namespace utility::datatype {

class ConvertUtility {
  public:
    template <std::size_t size> static std::vector<float> convertToVectorFloat1D(const float (&array)[size]);

    template <std::size_t size> static std::vector<unsigned int> convertToVectorUnsignedInt1D(const unsigned int (&array)[size]);
};

} // namespace utility::datatype