//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

CryptoRepositoryImp::CryptoRepositoryImp(SidProvider::SidProviderPtr token_provider_ptr) noexcept
    : token_provider_ptr{std::move(token_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  token_provider_ptr.reset();
}
StringEither CryptoRepositoryImp::GetSid() noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}

WStringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}

WStringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}
