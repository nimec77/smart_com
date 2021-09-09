//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

CryptoRepositoryImp::CryptoRepositoryImp(TokenProvider::TokenProviderPtr token_provider_ptr) noexcept
    : token_provider_ptr{std::move(token_provider_ptr)} {}

CryptoRepositoryImp::~CryptoRepositoryImp() noexcept {
  token_provider_ptr.reset();
}
StringEither CryptoRepositoryImp::GetSid() noexcept {
  return token_provider_ptr->GetToken().RightFlatMap([this](const auto token_ptr) {
    return token_provider_ptr->GetTokenInformation(token_ptr)
        .RightFlatMap([this](const auto token_info_ptr) {
          return token_provider_ptr->IsValidSidInToken(token_info_ptr)
              .RightFlatMap([token_info_ptr, this](const auto is_valid) {
                return token_provider_ptr->SidToString(token_info_ptr);
              });
        });
  });
}

WStringEither CryptoRepositoryImp::Encode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}

WStringEither CryptoRepositoryImp::Decode(const wchar_t *value) noexcept {
  return WStringEither::LeftOf(std::runtime_error("Not Implemented"));
}
