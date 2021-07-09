//
// Created by nim on 09.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_

#include <comdef.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <monad/either.h>
#include <smarteam/constatns.h>

namespace helper {

using Utf16ToUtf8Type = monad::Either<std::exception, const char*>;
Utf16ToUtf8Type Utf16ToUtf8(const wchar_t *utf16_str);
}

#endif//SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
