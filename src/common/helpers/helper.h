//
// Created by nim on 09.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_

#include <comdef.h>
#include <iostream>
#include <smarteam/constatns.h>
#include <sstream>
#include <common/base_types.h>

namespace helper {

CharPtrEtiher Utf16ToUtf8(const wchar_t *utf16_str) noexcept;
}

#endif//SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
