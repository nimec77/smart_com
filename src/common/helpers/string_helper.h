//
// Created by nim on 16.09.2021.
//

#ifndef SMART_COM_SRC_COMMON_HELPERS_STRING_HELPER_H_
#define SMART_COM_SRC_COMMON_HELPERS_STRING_HELPER_H_

#include <sstream>
#include <iomanip>
#include <common/base_types.h>
#include <common/helpers/helper.h>
#include <stdexcept>

namespace string_helper {
  BytesEither WStringToBytes(const std::wstring& text);

  StringEither BytesToHexString(const Bytes& data);
}

#endif//SMART_COM_SRC_COMMON_HELPERS_STRING_HELPER_H_
