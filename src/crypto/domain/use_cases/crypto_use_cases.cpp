//
// Created by nim on 08.09.2021.
//

#include "crypto_use_cases.h"

using WStringEither = CryptoUseCases::WStringEither;

CryptoUseCases::CryptoUseCases(CryptoRepository::CryptoRepositoryPtr crypto_repository_ptr) noexcept
    : crypto_repository_ptr(std::move(crypto_repository_ptr)) {}

CryptoUseCases::~CryptoUseCases() noexcept {
  crypto_repository_ptr.reset();
}

WStringEither CryptoUseCases::Encode(const wchar_t *value) noexcept {
  return crypto_repository_ptr->Encode(value);
}

WStringEither CryptoUseCases::Decode(const wchar_t *value) noexcept {
  return crypto_repository_ptr->Decode(value);
}