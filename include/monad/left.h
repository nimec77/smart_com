//
// Created by comrade77 on 06.07.2021.
//

#ifndef CPP_MONAD_LEFT_H
#define CPP_MONAD_LEFT_H

#include <memory>

namespace monad {
    template<typename T>
    struct Left {
        T value;
    };

    template<typename T>
    constexpr Left<T> left(const T &x) {
        return {x};
    }

    template<typename T>
    Left<T> left(T &&x) {
        return {std::forward<T>(x)};
    }
}// namespace monad

#endif//CPP_MONAD_LEFT_H
