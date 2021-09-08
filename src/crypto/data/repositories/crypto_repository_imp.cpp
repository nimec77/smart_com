//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

#include <utility>

using WStringEither = CryptoRepository::WStringEither;

CryptoRepositoryImp::CryptoRepositoryImp(TokenProvider::TokenProviderPtr token_provider_ptr) noexcept
    : token_provider_ptr{std::move(token_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  token_provider_ptr.reset();
}

CryptoRepository::WStringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return token_provider_ptr->GetToken().RightFlatMap([](const auto token) {
    return WStringEither::RightOf(L"Token");
  });
}

WStringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}
