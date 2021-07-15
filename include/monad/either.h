//
// Created by comrade77 on 06.07.2021.
//

#ifndef CPP_MONAD_EITHER_H
#define CPP_MONAD_EITHER_H

#include "left.h"
#include "right.h"

namespace monad {
    template<typename L, typename R>
    class Either {
    protected:
        union {
            L left_value;
            R right_value;
        };

    public:
        bool const isLeft = false;

        constexpr explicit Either(const Left<L> &l) : left_value{l.value}, isLeft{true} {};

        constexpr explicit Either(const Right<R> &r) : right_value{r.value}, isLeft{false} {};

        explicit Either(Left<L> &&l) : left_value{std::forward<L>(l.value)}, isLeft{true} {};

        explicit Either(Right<R> &&r) : right_value{std::forward<R>(r.value)}, isLeft{false} {};

        constexpr Either(const Either<L, R> &either) : isLeft(either.isLeft) {
            if (isLeft) {
                new (&left_value) L(either.left_value);
            } else {
                new (&right_value) R(either.right_value);
            }
        }

        virtual ~Either() {
            if (isLeft) {
                left_value.~L();
            } else {
                right_value.~R();
            }
        }

        static constexpr auto LeftOf(const L &l) {
            return Either<L, R>{monad::left(l)};
        }

        static constexpr auto RightOf(const R &r) {
            return Either<L, R>{monad::right(r)};
        }


        static auto LeftOf(const L &&l) {
            return Either<L, R>{monad::left(l)};
        }

        static auto RightOf(const R &&r) {
            return Either<L, R>{monad::right(r)};
        }

        template<typename LeftF, typename RightF>
        constexpr auto Fold(const LeftF &leftCase, const RightF &rightCase) const
                -> decltype(isLeft ? leftCase(left_value) : rightCase(right_value)) {
            return isLeft ? leftCase(left_value) : rightCase(right_value);
        }


        template<typename LeftF, typename RightF>
        constexpr void When(const LeftF &leftCase, const RightF &rightCase) const {
            isLeft ? leftCase(left_value) : rightCase(right_value);
        }

        template<typename F>
        constexpr void WhenLeft(const F &leftCase) const {
            if (isLeft) {
                leftCase(left_value);
            }
        }

        template<typename F>
        constexpr void WhenRight(const F &rightCase) const {
            if (!isLeft) {
                rightCase(right_value);
            }
        }

        template<typename LeftF>
        constexpr auto GetOrElse(const LeftF &leftCase) const
                -> decltype(isLeft ? leftCase(left_value) : right_value) {
            return isLeft ? leftCase(left_value) : right_value;
        }

        constexpr auto operator|(const R value) const {
            return isLeft ? value : right_value;
        }

        template<typename F>
        constexpr auto LeftMap(const F &leftCase) const
                -> Either<decltype(leftCase(left_value)), R> {
            using NextEither = Either<decltype(leftCase(left_value)), R>;
            return isLeft ? NextEither{monad::left(leftCase(left_value))} : NextEither{monad::right(right_value)};
        };

        template<typename F>
        constexpr auto LeftFlatMap(const F &leftCase) const
                -> decltype(leftCase(left_value)) {
            using NextEither = decltype(leftCase(left_value));
            return isLeft ? leftCase(left_value) : NextEither{monad::right(right_value)};
        }

        template<typename F>
        constexpr auto RightMap(const F &rightCase) const
                -> Either<L, decltype(rightCase(right_value))> {
            using NextEither = Either<L, decltype(rightCase(right_value))>;
            return isLeft ? NextEither{monad::left(left_value)} : NextEither{monad::right(rightCase(right_value))};
        };

        template<typename F>
        constexpr auto RightFlatMap(const F &rightCase) const
                -> decltype(rightCase(right_value)) {
            using NextEither = decltype(rightCase(right_value));
            return isLeft ? NextEither{monad::left(left_value)} : rightCase(right_value);
        }

        template<typename F>
        constexpr auto Map(const F &mapF) const
                -> decltype(mapF(*this)) {
            return mapF(*this);
        }

        constexpr explicit operator bool() const { return !isLeft; }

    private:
    };

    template<typename L, typename R>
    constexpr bool operator==(const Either<L, R> &a, const Either<L, R> &b) {
        if (a.isLeft) {
            if (b.isLeft) {
                return a.left_value == b.left_value;
            }
        } else {
            if (!b.isLeft) {
                return a.right_value == b.right_value;
            }
        }

        return false;
    }

    template<typename L, typename R>
    constexpr bool operator!=(const Either<L, R> &a, const Either<L, R> &b) {
        return !(a == b);
    }
}// namespace monad


#endif//CPP_MONAD_EITHER_H
