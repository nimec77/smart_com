//
// Created by nim on 16.09.2021.
//

#include "string_helper.h"

namespace string_helper {
BytesEither WStringToBytes(const std::wstring &text) {
  return helper::Utf16ToUtf8(text.c_str()).RightFlatMap([](const auto str) {
    return BytesEither::RightOf({str.begin(), str.end()});
  });
}

StringEither BytesToHexString(const Bytes &data) {
  std::stringstream string_stream_;

  string_stream_ << std::hex;
  for (int item : data) {
    string_stream_ << std::setw(2) << std::setfill('0') << item;
  }

  return StringEither::RightOf(string_stream_.str());
}
}// namespace string_helper