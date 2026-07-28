#pragma once

namespace core::structs {

template <typename T> struct Vector3 {
    union {
        struct {
            T x;
            T y;
            T z;
        };

        struct {
            T r;
            T g;
            T b;
        };
    };

    constexpr Vector3() : x{}, y{}, z{} {
    }

    constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {
    }
};

} // namespace core::structs
