//
// Created by nim on 09.09.2021.
//

#ifndef SMART_COM_SRC_COMMON_BASE_TYPES_H_
#define SMART_COM_SRC_COMMON_BASE_TYPES_H_

#include <string>
#include <vector>
#include <comutil.h>
#include <monad/either.h>
#include <windows.h>

using BoolEither = monad::Either<std::exception, bool>;
using CharPtrEtiher = monad::Either<std::exception, const char*>;
using WStringEither = monad::Either<std::exception, std::wstring>;
using BstrEither = monad::Either<std::exception, _bstr_t>;
using StringEither = monad::Either<std::exception, std::string>;
using ClassIdEither = monad::Either<std::exception, CLSID>;
using NamesEither = monad::Either<std::exception, DISPID>;
using IDispatchEither = monad::Either<std::exception, IDispatch *>;
using SharedPtr = std::shared_ptr<void>;
using SharedPtrEither = monad::Either<std::exception, SharedPtr>;
using SidPtr = std::shared_ptr<SID>;
using SidEither = monad::Either<std::exception, SidPtr>;
using Bytes = std::vector<BYTE>;
using BytesEither = monad::Either<std::exception, Bytes>;

#endif//SMART_COM_SRC_COMMON_BASE_TYPES_H_
