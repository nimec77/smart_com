//
// Created by nim on 08.09.2021.
//

#include "crypto_repository_imp.h"

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

StringEither CryptoRepositoryImp::Encode(std::wstring secret_key, std::wstring text) noexcept {
  return string_helper::WStringToBytes(secret_key).RightFlatMap([this, text](const auto key_data) {
    return crypto_provider_ptr->Md5Hash(key_data).RightFlatMap([this, text](const auto key_md5) {
      return string_helper::WStringToBytes(text).RightFlatMap([this, key_md5](const auto text_data) {
        return crypto_provider_ptr->EncodeAes(key_md5, text_data).RightFlatMap([](const auto data) {
          return string_helper::BytesToHexString(data);
        });
      });
    });
  });
}

StringEither CryptoRepositoryImp::Decode(std::wstring secret_key, std::wstring hex_value) noexcept {
  return StringEither::LeftOf(std::runtime_error("Not Implemented"));
}
