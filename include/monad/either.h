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
        const Left<nullptr_t> leftEmpty = Left<nullptr_t>{nullptr};
        const Right<nullptr_t> rightEmpty = Right<nullptr_t>{nullptr};

        bool const isLeft = false;

        constexpr explicit Either(Left<L> const &l) : left_value{l.value}, isLeft{true} {};

        constexpr explicit Either(Right<R> const &r) : right_value{r.value}, isLeft{false} {};

        explicit Either(Left<L> &&l) : left_value{std::forward<L>(l.value)}, isLeft{true} {};

        explicit Either(Right<R> &&r) : right_value{std::forward<R>(r.value)}, isLeft{false} {};

        constexpr Either(Either<L, R> const &either) : isLeft(either.isLeft) {
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

        static constexpr auto LeftOf(L const &l) {
            return Either<L, R>{monad::left(l)};
        }

        static constexpr auto RightOf(R const &r) {
            return Either<L, R>{monad::right(r)};
        }


        static auto LeftOf(L &&l) {
            return Either<L, R>{monad::left(l)};
        }

        static auto RightOf(R &&r) {
            return Either<L, R>{monad::right(r)};
        }

        template<typename LeftF, typename RightF>
        auto Fold(LeftF const &leftCase, RightF const &rightCase) const
                -> decltype(isLeft ? leftCase(left_value) : rightCase(right_value)) {
            return isLeft ? leftCase(left_value) : rightCase(right_value);
        }


        template<typename LeftF, typename RightF>
        void When(LeftF const &leftCase, RightF const &rightCase) {
            isLeft ? leftCase(left_value) : rightCase(right_value);
        }

        template<typename F>
        void WhenLeft(F const &leftCase) {
            if (isLeft) {
                leftCase(left_value);
            }
        }

        template<typename F>
        void WhenRight(F const &rightCase) {
            if (!isLeft) {
                rightCase(right_value);
            }
        }

        template<typename LeftF>
        auto GetOrElse(LeftF const &leftCase) const
                -> decltype(isLeft ? leftCase(left_value) : right_value) {
            return isLeft ? leftCase(left_value) : right_value;
        }

        auto operator|(const R value) {
            return isLeft ? value : right_value;
        }

        template<typename F>
        auto LeftMap(F const &leftCase) const
                -> Either<decltype(leftCase(left_value)), R> {
            using NextEither = Either<decltype(leftCase(left_value)), R>;
            return isLeft ? NextEither{monad::left(leftCase(left_value))} : NextEither{monad::right(right_value)};
        };

        template<typename F>
        auto LeftFlatMap(F const &leftCase) const
                -> decltype(leftCase(left_value)) {
            using NextEither = decltype(leftCase(left_value));
            return isLeft ? leftCase(left_value) : NextEither{monad::right(right_value)};
        }

        template<typename F>
        auto RightMap(F const &rightCase) const
                -> Either<L, decltype(rightCase(right_value))> {
            using NextEither = Either<L, decltype(rightCase(right_value))>;
            return isLeft ? NextEither{monad::left(left_value)} : NextEither{monad::right(rightCase(right_value))};
        };

        template<typename F>
        auto RightFlatMap(F const &rightCase) const
                -> decltype(rightCase(right_value)) {
            using NextEither = decltype(rightCase(right_value));
            return isLeft ? NextEither{monad::left(left_value)} : rightCase(right_value);
        }

        constexpr explicit operator bool() const { return !isLeft; }

    private:
    };

    template<typename L, typename R>
    bool operator==(Either<L, R> const &a, Either<L, R> const &b) {
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
    bool operator!=(Either<L, R> const &a, Either<L, R> const &b) {
        return !(a == b);
    }
}// namespace monad


#endif//CPP_MONAD_EITHER_H
