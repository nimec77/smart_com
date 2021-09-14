//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

CryptoRepositoryImp::CryptoRepositoryImp(SidProvider::SidProviderPtr sid_provider_ptr) noexcept
    : sid_provider_ptr{std::move(sid_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  sid_provider_ptr.reset();
}
StringEither CryptoRepositoryImp::GetSid() noexcept {
  return sid_provider_ptr->GetName()
      .RightFlatMap([this](const auto username) {
        return sid_provider_ptr->GetAccountSidFromName(username)
            .RightFlatMap([](const auto w_sid) {
              return helper::Utf16ToUtf8(w_sid.c_str());
            });
      });
}

StringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}

StringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}
