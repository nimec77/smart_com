//
// Created by nim on 09.09.2021.
//

#ifndef SMART_COM_SRC_COMMON_BASE_TYPES_H_
#define SMART_COM_SRC_COMMON_BASE_TYPES_H_

#include <comutil.h>
#include <monad/either.h>
#include <windows.h>

using BoolEither = monad::Either<std::exception, bool>;
using CharPtrEtiher = monad::Either<std::exception, const char*>;
using BstrEither = monad::Either<std::exception, _bstr_t>;
using ClassIdEither = monad::Either<std::exception, CLSID>;
using NamesEither = monad::Either<std::exception, DISPID>;
using IDispatchEither = monad::Either<std::exception, IDispatch *>;
using HandlePtr = std::shared_ptr<void>;
using HandleEither = monad::Either<std::exception, HandlePtr>;
using WStringEither = monad::Either<std::exception, const wchar_t *>;

#endif//SMART_COM_SRC_COMMON_BASE_TYPES_H_
