#pragma once

namespace core::structs {

template <typename T> struct Vector4 {
    union {
        struct {
            T w;
            T x;
            T y;
            T z;
        };

        struct {
            T r;
            T g;
            T b;
            T a;
        };
    };

    constexpr Vector4() : x{}, y{}, z{}, w{} {
    }

    constexpr Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }
};

} // namespace core::structs
