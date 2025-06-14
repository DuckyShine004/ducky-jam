#include <utility/datatype/ConvertUtility.hpp>

#include <cstring>

namespace utility::datatype {

template <std::size_t size> static std::vector<float> convertToVectorFloat1D(const float (&array)[size]) {
    std::vector<float> vector(size);

    memcpy(vector.data(), array, size * sizeof(float));

    return vector;
}

template <std::size_t size> static std::vector<unsigned int> convertToVectorUnsignedInt1D(const unsigned int (&array)[size]) {
    std::vector<unsigned int> vector(size);

    memcpy(vector.data(), array, size * sizeof(unsigned int));

    return vector;
}

} // namespace utility::datatype