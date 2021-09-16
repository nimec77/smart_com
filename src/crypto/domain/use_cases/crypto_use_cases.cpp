//
// Created by nim on 08.09.2021.
//

#include "crypto_use_cases.h"

CryptoUseCases::CryptoUseCases(CryptoRepository::CryptoRepositoryPtr crypto_repository_ptr) noexcept
    : crypto_repository_ptr(std::move(crypto_repository_ptr)) {
}

CryptoUseCases::~CryptoUseCases() noexcept {
  crypto_repository_ptr.reset();
}

StringEither CryptoUseCases::Encode(const std::wstring& value) noexcept {
  return crypto_repository_ptr->GetSid()
      .RightFlatMap([this, value](const auto sid) {
        return crypto_repository_ptr->Encode(sid, value);
      });
}

StringEither CryptoUseCases::Decode(const std::wstring& hex_value) noexcept {
  return crypto_repository_ptr->GetSid()
  .RightFlatMap([this, hex_value](const auto sid) {
    return crypto_repository_ptr->Decode(sid, hex_value);
  });
}
