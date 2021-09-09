//
// Created by nim on 09.09.2021.
//

#include "token_provider_imp.h"

WStringEither TokenProviderImp::GetName() noexcept {
  wchar_t username_[UNLEN + 1];
  DWORD username_len_ = UNLEN + 1;

  const auto result_ = GetUserNameW(username_, &username_len_);
  if (!result_) {
    return WStringEither::LeftOf(std::runtime_error("TokenProvider::GetName GetUserNameW error:"));
  }

  return WStringEither::RightOf(std::wstring{username_});
}

WStringEither TokenProviderImp::GetAccountSidFromName(std::wstring username) noexcept {
  SID_NAME_USE sid_name_use_ = SidTypeInvalid;
  BYTE sid_buf_[SECURITY_MAX_SID_SIZE];
  DWORD sid_size_ = sizeof(sid_buf_);
  PSID sid_ = (PSID) sid_buf_;
  LPWSTR domain_name_ = nullptr;
  DWORD domain_name_size_ = 0;

  auto result = LookupAccountNameW(
      nullptr,
      username.c_str(),
      sid_,
      &sid_size_,
      domain_name_,
      &domain_name_size_,
      &sid_name_use_);

  if (!result) {
    const auto error = GetLastError();
    if (error != ERROR_INSUFFICIENT_BUFFER) {
      return WStringEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage(
              "TokenProvider::GetAccountSidFromName LookupAccountNameLocalW error:", error)));
    }
    domain_name_ = (LPWSTR) LocalAlloc(LPTR, domain_name_size_ * sizeof(*domain_name_));
    if (domain_name_ == nullptr) {
      return WStringEither::LeftOf(
          std::runtime_error("TokenProvider::GetAccountSidFromName LocalAlloc error: ERROR_OUTOFMEMORY"));
    }
    result = LookupAccountNameW(
        nullptr,
        username.c_str(),
        sid_,
        &sid_size_,
        domain_name_,
        &domain_name_size_,
        &sid_name_use_);

    LocalFree(domain_name_);
    if (!result) {
      return WStringEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("TokenProvider::GetAccountSidFromName LookupAccountNameLocalW error:",
                                        GetLastError())));
    }

    LPWSTR string_sid_ = nullptr;
    result = ConvertSidToStringSidW(sid_, &string_sid_);
    if (!result) {
      return WStringEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("TokenProvider::GetAccountSidFromName ConvertSidToStringSid error:",
                                        GetLastError())));
    }
    const auto sid_result_ = std::wstring(string_sid_);
    LocalFree(string_sid_);

    return WStringEither::RightOf(sid_result_);
  }

  return WStringEither::LeftOf(std::runtime_error("TokenProvider::GetAccountSidFromName unknown error"));
}
