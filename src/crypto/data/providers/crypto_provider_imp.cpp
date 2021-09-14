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
  if (aes_alg_ptr) {
    return BoolEither::RightOf(true);
  }

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
  aes_alg_ptr = data_helper::MakeAlgorithmSharedPtr(aes_alg_);

  DWORD data_size_ = 0;
  status_ = BCryptGetProperty(
      aes_alg_ptr.get(),
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
      aes_alg_ptr.get(),
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
      aes_alg_ptr.get(),
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
  return InitAes().RightFlatMap([this, &key_data, &data](const auto init) {
    auto key_object_ptr_ = data_helper::MakeHeapUniquePtr(key_object_size);
    if (!key_object_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::EncodeAes MakeHeapUniquePtr error on key object"));
    }

    BCRYPT_KEY_HANDLE key_handle_;
    auto status_ = BCryptGenerateSymmetricKey(
        aes_alg_ptr.get(),
        &key_handle_,
        key_object_ptr_.get(),
        key_object_size,
        (PBYTE) key_data.data(),
        key_data.size(),
        0);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::EncodeAes BCryptGenerateSymmetricKey error:",
                                        status_)));
    }
    auto key_handle_ptr_ = data_helper::MakeKeyHandleUniquePtr(key_handle_);

    auto plain_text_size_ = data.size();
    auto plain_text_ptr_ = data_helper::MakeHeapUniquePtr(plain_text_size_);
    if (!plain_text_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::EncodeAes MakeHeapUniquePtr error on plain text"));
    }
    memcpy(plain_text_ptr_.get(), data.data(), plain_text_size_);

    auto iv_ptr_ = data_helper::MakeHeapUniquePtr(block_length);
    if (!iv_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::EncodeAes MakeHeapUniquePtr error on IV"));
    }
    memcpy(iv_ptr_.get(), rgb_iv, block_length);

    DWORD cipher_text_size_ = 0;
    status_ = BCryptEncrypt(
        key_handle_ptr_.get(),
        plain_text_ptr_.get(),
        plain_text_size_,
        nullptr,
        iv_ptr_.get(),
        block_length,
        nullptr,
        0,
        &cipher_text_size_,
        BCRYPT_BLOCK_PADDING);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::EncodeAes BCryptEncrypt error:",
                                        status_)));
    }

    auto cipher_text_ptr_ = data_helper::MakeHeapUniquePtr(cipher_text_size_);
    if (!cipher_text_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::EncodeAes MakeHeapUniquePtr error on cipher text"));
    }

    DWORD data_size_ = 0;
    status_ = BCryptEncrypt(
        key_handle_ptr_.get(),
        plain_text_ptr_.get(),
        plain_text_size_,
        nullptr,
        iv_ptr_.get(),
        block_length,
        cipher_text_ptr_.get(),
        cipher_text_size_,
        &data_size_,
        BCRYPT_BLOCK_PADDING);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::EncodeAes BCryptEncrypt error:",
                                        status_)));
    }

    return BytesEither::RightOf({cipher_text_ptr_.get(), cipher_text_ptr_.get() + data_size_});
  });
}

BytesEither CryptoProviderImp::DecodeAes(const Bytes &key_data, const Bytes &data) noexcept {
  return InitAes().RightFlatMap([this, &key_data, &data](const auto init) {
    auto key_object_ptr_ = data_helper::MakeHeapUniquePtr(key_object_size);
    if (!key_object_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::DecodeAes MakeHeapUniquePtr error on key object"));
    }

    BCRYPT_KEY_HANDLE key_handle_;
    auto status_ = BCryptGenerateSymmetricKey(
        aes_alg_ptr.get(),
        &key_handle_,
        key_object_ptr_.get(),
        key_object_size,
        (PBYTE) key_data.data(),
        key_data.size(),
        0);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::DecodeAes BCryptGenerateSymmetricKey error:",
                                        status_)));
    }
    auto key_handle_ptr_ = data_helper::MakeKeyHandleUniquePtr(key_handle_);

    auto iv_ptr_ = data_helper::MakeHeapUniquePtr(block_length);
    if (!iv_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::DecodeAes MakeHeapUniquePtr error on IV"));
    }
    memcpy(iv_ptr_.get(), rgb_iv, block_length);

    DWORD data_size_ = 0;
    status_ = BCryptDecrypt(
        key_handle_ptr_.get(),
        (PBYTE) data.data(),
        data.size(),
        nullptr,
        iv_ptr_.get(),
        block_length,
        nullptr,
        0,
        &data_size_,
        BCRYPT_BLOCK_PADDING);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::EncodeAes BCryptDecrypt error:",
                                        status_)));
    }

    auto plain_text_ptr_ = data_helper::MakeHeapUniquePtr(data_size_);
    if (!plain_text_ptr_) {
      return BytesEither::LeftOf(std::runtime_error("CryptoProvider::DecodeAes MakeHeapUniquePtr error on plain text"));
    }

    status_ = BCryptDecrypt(
        key_handle_ptr_.get(),
        (PBYTE) data.data(),
        data.size(),
        nullptr,
        iv_ptr_.get(),
        block_length,
        plain_text_ptr_.get(),
        data_size_,
        &data_size_,
        BCRYPT_BLOCK_PADDING);
    if (!NT_SUCCESS(status_)) {
      return BytesEither::LeftOf(std::runtime_error(
          data_helper::MakeErrorMessage("CryptoProvider::EncodeAes BCryptDecrypt error:",
                                        status_)));
    }

    return BytesEither::RightOf({plain_text_ptr_.get(), plain_text_ptr_.get() + data_size_});
  });
}
