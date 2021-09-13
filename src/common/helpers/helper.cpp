//
// Created by nim on 09.07.2021.
//

#include "helper.h"

namespace helper {
CharPtrEtiher Utf16ToUtf8(const wchar_t *utf16_str) noexcept {
  auto size = WideCharToMultiByte(
      smarteam::kConsoleCodePage,
      0,
      utf16_str,
      -1,
      nullptr,
      0,
      nullptr,
      nullptr);
  if (size == 0) {
    return CharPtrEtiher::LeftOf(
        std::length_error("helper::Utf16ToUtf8 WideCharToMultiByte error get string length"));
  }

  const auto result = new char[size];

  size = WideCharToMultiByte(
      smarteam::kConsoleCodePage,
      0,
      utf16_str,
      -1,
      result,
      size,
      nullptr,
      nullptr);
  if (size == 0) {
    return CharPtrEtiher::LeftOf(
        std::runtime_error("helper:Utf16ToUtf8 WideCharToMultiByte error translate string to utf8"));
  }

  return CharPtrEtiher::RightOf(result);
}

}// namespace helper
