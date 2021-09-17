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

WStringEither BytesToHexWString(const Bytes& data) {
  std::wstringstream string_stream_;

  string_stream_ << std::hex;
  for (int item : data) {
    string_stream_ << std::setw(2) << std::setfill(L'0') << item;
  }

  return WStringEither::RightOf(string_stream_.str());

}

BytesEither HexStringToBytes(const std::string &hex_text) {
  auto result_ = Bytes{};
  try {
    for (auto i = 0; i < hex_text.length(); i += 2) {
      result_.push_back(std::stoul(hex_text.substr(i, 2), nullptr, 16));
    }
  } catch (std::invalid_argument &e) {
    return BytesEither::LeftOf(e);
  } catch (std::out_of_range &e) {
    return BytesEither::LeftOf(e);
  }
  return BytesEither::RightOf(result_);
}
}// namespace string_helper