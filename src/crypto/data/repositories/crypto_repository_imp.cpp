//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

CryptoRepositoryImp::CryptoRepositoryImp(TokenProvider::TokenProviderPtr token_provider_ptr) noexcept
    : token_provider_ptr{std::move(token_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  token_provider_ptr.reset();
}

WStringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return token_provider_ptr->GetToken().RightFlatMap([this](const auto token_ptr) {
    return token_provider_ptr->GetTokenInformation(token_ptr).RightFlatMap([](const auto token_info_ptr){
      return WStringEither::RightOf(L"Token Info");
    });
  });
}

WStringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}
