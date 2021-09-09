//
// Created by nim on 09.09.2021.
//

#ifndef SMART_COM_SRC_COMMON_BASE_TYPES_H_
#define SMART_COM_SRC_COMMON_BASE_TYPES_H_

#include <monad/either.h>
#include <windows.h>

using CharPtrEtiher = monad::Either<std::exception, const char*>;
using ClassIdEither = monad::Either<std::exception, CLSID>;
using NamesEither = monad::Either<std::exception, DISPID>;
using HandlePtr = std::shared_ptr<void>;
using HandleEither = monad::Either<std::exception, HandlePtr>;

#endif//SMART_COM_SRC_COMMON_BASE_TYPES_H_
