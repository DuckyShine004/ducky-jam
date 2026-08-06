#pragma once

namespace core::structs {

template <typename T> struct Vector2 {
    union {
        struct {
            T x;
            T y;
        };

        struct {
            T u;
            T v;
        };

        struct {
            T w;
            T h;
        };
    };

    constexpr Vector2() : x{}, y{} {
    }

    constexpr Vector2(T x, T y) : x(x), y(y) {
    }

    template <typename S> Vector2 &operator*=(S scalar) {
        x *= scalar;
        y *= scalar;

        return *this;
    }
};

} // namespace core::structs
