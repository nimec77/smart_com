//
// Created by nim on 09.07.2021.
//

#include "helper.h"

namespace helper {
Utf16ToUtf8Type Utf16ToUtf8(const wchar_t *utf16_str) {
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
    auto exception = std::length_error("helper::Utf16ToUtf8 WideCharToMultiByte error get string length");
    return Utf16ToUtf8Type::LeftOf(exception);
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
    auto exception = std::runtime_error("helper:Utf16ToUtf8 WideCharToMultiByte error translate string to utf8");
    return Utf16ToUtf8Type::LeftOf(exception);
  }

  return Utf16ToUtf8Type::RightOf(result);
}

}// namespace helper
