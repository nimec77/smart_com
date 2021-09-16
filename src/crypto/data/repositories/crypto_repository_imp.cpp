//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

#include <utility>

CryptoRepositoryImp::CryptoRepositoryImp(SidProvider::SidProviderPtr sid_provider_ptr,
                                         CryptoProvider::CryptoProviderPtr crypto_provider_ptr) noexcept
    : sid_provider_ptr{std::move(sid_provider_ptr)}, crypto_provider_ptr{std::move(crypto_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  sid_provider_ptr.reset();
  crypto_provider_ptr.reset();
}

WStringEither CryptoRepositoryImp::GetSid() noexcept {
  return sid_provider_ptr->GetName()
      .RightFlatMap([this](const auto username) {
        return sid_provider_ptr->GetAccountSidFromName(username);
      });
}

StringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}

StringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}
