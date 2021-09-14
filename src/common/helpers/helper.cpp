//
// Created by nim on 09.07.2021.
//

#include "helper.h"

namespace helper {
StringEither Utf16ToUtf8(const wchar_t *utf16_str) noexcept {
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
    return StringEither::LeftOf(
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
    return StringEither::LeftOf(
        std::runtime_error("helper:Utf16ToUtf8 WideCharToMultiByte error translate string to utf8"));
  }

  return StringEither::RightOf({result});
}

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

SharedPtr MakeHandleSharedPtr(HANDLE handle) noexcept {
  if (handle == INVALID_HANDLE_VALUE || handle == nullptr) {
    return nullptr;
  }

  return {handle, HandleDeleter()};
}

SharedPtr MakeAlgorithmSharedPtr(BCRYPT_ALG_HANDLE alg_handle) noexcept {
  if (alg_handle == nullptr) {
    return nullptr;
  }

  return {alg_handle, CloseAlgorithm()};
}

HeapUniquePtr MakeHeapUniquePtr(DWORD size) noexcept {
  const auto pointer = (PBYTE) HeapAlloc(GetProcessHeap(), 0, size);

  return HeapUniquePtr{pointer};
}

KeyUniqueHandlePtr MakeKeyHandleUniquePtr(BCRYPT_KEY_HANDLE key_handle) noexcept {
  return KeyUniqueHandlePtr{key_handle};
}

}// namespace helper
