//
// Created by comrade77 on 06.07.2021.
//

#ifndef CPP_MONAD_RIGHT_H
#define CPP_MONAD_RIGHT_H

#include <memory>

namespace monad {
    template<typename T>
    struct Right {
        T value;
    };

    template<typename T>
    constexpr Right<T> right(T const &x) {
        return {x};
    }

    template<typename T>
    constexpr Right<T> right(T &&x) {
        return {std::forward<T>(x)};
    }

}// namespace monad

#endif//CPP_MONAD_RIGHT_H
