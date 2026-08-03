#pragma once

#include "core/structs/vector3.hpp"

namespace core::structs {

template <typename T> struct Vector4 {
    union {
        struct {
            T x;
            T y;
            T z;
            T w;
        };

        struct {
            T r;
            T g;
            T b;
            T a;
        };

        // Vector3 rgb;
    };

    constexpr Vector4() : x{}, y{}, z{}, w{} {
    }

    constexpr Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }

    constexpr Vector3<T> rgb() const {
        return {r, g, b};
    }
};

} // namespace core::structs
