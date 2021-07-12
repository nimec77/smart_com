//
// Created by nim on 05.07.2021.
//

#include "data_helper.h"
namespace data_helper {

std::string MakeErrorMessage(const std::string &error, long code) {
  std::stringstream str_stream;
  str_stream << error << " " << std::hex << code;

  return str_stream.str();
}

void SafeRelease(IDispatch &dispatch) {
  dispatch.Release();
}

ClassIdEither GetClassId(const wchar_t *prog_id) {
  CLSID clsid;

  auto hr = CLSIDFromProgID(prog_id, &clsid);
  if (FAILED(hr)) {
    auto message = MakeErrorMessage("data_helper::GetClassId CLSIDFromProgID error:", hr);
    auto exception = std::invalid_argument(message);
    return ClassIdEither::LeftOf(exception);
  }

  return ClassIdEither::RightOf(clsid);
}
NamesEither GetNames(IDispatch &dispatch, const wchar_t *name) {
  DISPID dispid{};

  auto hr = dispatch.GetIDsOfNames(IID_NULL, const_cast<LPOLESTR *>(&name), 1, LOCALE_USER_DEFAULT, &dispid);
  if (FAILED(hr)) {
    return helper::Utf16ToUtf8(name).RightFlatMap([hr](const auto str) {
      std::stringstream str_stream;
      str_stream << "data_helper::GetNames GetIDsOfNames '" << str << "' error: ";
      auto message = MakeErrorMessage(str_stream.str(), hr);
      auto exception = std::runtime_error(message);
      return NamesEither::LeftOf(exception);
    });
  }

  return NamesEither::RightOf(dispid);
}
}// namespace data_helper
