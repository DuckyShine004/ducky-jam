#include <utility/bit/BitUtility.hpp>

namespace utility::bit {

bool BitUtility::isBitSet(const int position, const int mask) {
    return mask & (1 << position);
}

} // namespace utility::bit