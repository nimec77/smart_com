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
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptOpenAlgorithmProvider error:",
                                      status_)));
  }
  auto md5_alg_ptr_ = data_helper::MakeAlgorithmSharedPtr(md5_alg_);

  DWORD hash_object_size_ = 0;
  DWORD data_size_ = 0;

  status_ = BCryptGetProperty(
      md5_alg_ptr_.get(),
      BCRYPT_OBJECT_LENGTH,
      (PBYTE) &hash_object_size_,
      sizeof(DWORD),
      &data_size_,
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptGetProperty error:",
                                      status_)));
  }
  auto hash_object_ptr_ = data_helper::MakeHeapUniquePtr(hash_object_size_);
  if (!hash_object_ptr_) {
    return BytesEither::LeftOf(std::runtime_error("CryptoProvider::Md5Hash MakeHeapUniquePtr error on hash object"));
  }

  DWORD hash_size_ = 0;
  status_ = BCryptGetProperty(
      md5_alg_ptr_.get(),
      BCRYPT_HASH_LENGTH,
      (PBYTE) &hash_size_,
      sizeof(DWORD),
      &data_size_,
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptGetProperty error:",
                                      status_)));
  }
  auto hash_ptr_ = data_helper::MakeHeapUniquePtr(hash_size_);
  if (!hash_ptr_) {
    return BytesEither::LeftOf(std::runtime_error("CryptoProvider::Md5Hash MakeHeapUniquePtr error on hash"));
  }

  BCRYPT_HASH_HANDLE hash_handle_;
  status_ = BCryptCreateHash(
      md5_alg_ptr_.get(),
      &hash_handle_,
      hash_object_ptr_.get(),
      hash_object_size_,
      nullptr,
      0,
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptCreateHash error:",
                                      status_)));
  }
  auto hash_handle_ptr_ = data_helper::MakeKeyHandleUniquePtr(hash_handle_);

  status_ = BCryptHashData(
      hash_handle_ptr_.get(),
      (PBYTE) data.data(),
      data.size(),
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptHashData error:",
                                      status_)));
  }

  status_ = BCryptFinishHash(
      hash_handle_ptr_.get(),
      hash_ptr_.get(),
      hash_size_,
      0);
  if (!NT_SUCCESS(status_)) {
    return BytesEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::Md5Hash BCryptFinishHash error:",
                                      status_)));
  }

  return BytesEither::RightOf({hash_ptr_.get(), hash_ptr_.get() + hash_size_});
}

BoolEither CryptoProviderImp::InitAes() noexcept {
  BCRYPT_ALG_HANDLE aes_alg_;
  auto status_ = BCryptOpenAlgorithmProvider(
      &aes_alg_,
      BCRYPT_AES_ALGORITHM,
      nullptr,
      0);
  if (!NT_SUCCESS(status_)) {
    return BoolEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::InitAes BCryptOpenAlgorithmProvider error:",
                                      status_)));
  }
  auto aes_alg_ptr_ = data_helper::MakeAlgorithmSharedPtr(aes_alg_);

  DWORD data_size_ = 0;
  status_ = BCryptGetProperty(
      aes_alg_ptr_.get(),
      BCRYPT_OBJECT_LENGTH,
      (PBYTE) &key_object_size,
      sizeof(DWORD),
      &data_size_,
      0);
  if (!NT_SUCCESS(status_)) {
    return BoolEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::InitAes BCryptGetProperty error:",
                                      status_)));
  }

  status_ = BCryptGetProperty(
      aes_alg_ptr_.get(),
      BCRYPT_BLOCK_LENGTH,
      (PBYTE) &block_length,
      sizeof(DWORD),
      &data_size_,
      0);
  if (!NT_SUCCESS(status_)) {
    return BoolEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::InitAes BCryptGetProperty error:",
                                      status_)));
  }

  if (block_length > sizeof(rgb_iv)) {
    return BoolEither::LeftOf(
        std::runtime_error("CryptoProvider::InitAes Block length is longer then the provided IV length"));
  }

  status_ = BCryptSetProperty(
      aes_alg_ptr_.get(),
      BCRYPT_CHAINING_MODE,
      (PBYTE) BCRYPT_CHAIN_MODE_CBC,
      sizeof(BCRYPT_CHAIN_MODE_CBC),
      0);
  if (!NT_SUCCESS(status_)) {
    return BoolEither::LeftOf(std::runtime_error(
        data_helper::MakeErrorMessage("CryptoProvider::InitAes BCryptSetProperty error:",
                                      status_)));
  }

  return BoolEither::RightOf(true);
}

BytesEither CryptoProviderImp::EncodeAes(const Bytes &key_data, const Bytes &data) noexcept {
  return BytesEither::LeftOf(std::runtime_error("Not Implemented"));
}

BytesEither CryptoProviderImp::DecodeAes(const Bytes &data) noexcept {
  return BytesEither::LeftOf(std::runtime_error("Not Implemented"));
}
