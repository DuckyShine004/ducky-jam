#include <utility/datatype/ConvertUtility.hpp>

#include <cstring>

namespace utility::datatype {

static std::vector<float> convertToVectorFloat1D(const float array[]) {
    int size = sizeof(array) / sizeof(array[0]);

    std::vector<float> vector(size);

    memcpy(vector.data(), array, size * sizeof(float));

    return vector;
}

} // namespace utility::datatype