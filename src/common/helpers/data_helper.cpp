//
// Created by nim on 05.07.2021.
//

#include "data_helper.h"
namespace data_helper {

std::string MakeErrorMessage(const std::string &error, unsigned long code) noexcept {
  std::stringstream str_stream;
  str_stream << error << " " << std::hex << code;

  return str_stream.str();
}

void SafeRelease(IDispatch *dispatch) noexcept {
  if (dispatch != nullptr) {
    dispatch->Release();
    dispatch = nullptr;
  }
}

ClassIdEither GetClassId(const wchar_t *prog_id) noexcept {
  CLSID clsid;

  const auto hr_ = CLSIDFromProgID(prog_id, &clsid);
  if (FAILED(hr_)) {
    return ClassIdEither::LeftOf(
        std::invalid_argument(MakeErrorMessage("data_helper::GetClassId CLSIDFromProgID error:", hr_)));
  }

  return ClassIdEither::RightOf(clsid);
}
NamesEither GetNames(IDispatch &dispatch, const wchar_t *name) noexcept {
  DISPID dispid_{};

  const auto hr_ = dispatch.GetIDsOfNames(IID_NULL, const_cast<LPOLESTR *>(&name), 1, LOCALE_USER_DEFAULT, &dispid_);
  if (FAILED(hr_)) {
    return helper::Utf16ToUtf8(name).RightFlatMap([hr_](const auto str) {
      std::string error{"data_helper::GetNames GetIDsOfNames '"};
      return NamesEither::LeftOf(
          std::runtime_error(MakeErrorMessage(error + str + std::string{"' error:"}, hr_)));
    });
  }

  return NamesEither::RightOf(dispid_);
}

HandlePtr MakeHandleSharedPtr(HANDLE handle) noexcept {
  if (handle == INVALID_HANDLE_VALUE || handle == nullptr) {
    return nullptr;
  }

  return {handle, HandleDeleter()};
}

}// namespace data_helper
