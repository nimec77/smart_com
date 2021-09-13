//
// Created by nim on 13.09.2021.
//

#include "crypto_provider_imp.h"

BytesEither CryptoProviderImp::Md5Hash(const Bytes &data) noexcept {
  BCRYPT_ALG_HANDLE md5_alg_;
  auto status_ = BCryptOpenAlgorithmProvider(
      &md5_alg_,
      BCRYPT_MD5_ALGORITHM,
      nullptr,
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("SidProvider::GetAccountSidFromName LookupAccountNameLocalW error:",
                                      status_)));
  }


  return BytesEither::LeftOf(std::runtime_error("Not Implemented"));
}

BoolEither CryptoProviderImp::InitAes() noexcept {
  return BoolEither::LeftOf(std::runtime_error("Not Implemented"));
}

BytesEither CryptoProviderImp::EncodeAes(const Bytes &key_data, const Bytes &data) noexcept {
  return BytesEither::LeftOf(std::runtime_error("Not Implemented"));
}

BytesEither CryptoProviderImp::DecodeAes(const Bytes &data) noexcept {
  return BytesEither::LeftOf(std::runtime_error("Not Implemented"));
}
