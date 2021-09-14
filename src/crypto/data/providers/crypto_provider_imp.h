//
// Created by nim on 13.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_

#include <common/helpers/helper.h>
#include <crypto/data/ports/providers/crypto_provider.h>
#include <stdexcept>

#define NT_SUCCESS(status) (((NTSTATUS) (status)) >= 0)

class CryptoProviderImp : public CryptoProvider {

 public:
  CryptoProviderImp() noexcept = default;

  ~CryptoProviderImp() override = default;

  BytesEither Md5Hash(const Bytes &data) noexcept override;
  BytesEither EncodeAes(const Bytes &key_data, const Bytes &data) noexcept override;
  BytesEither DecodeAes(const Bytes &key_data, const Bytes &data) noexcept override;

 private:
  constexpr static const BYTE rgb_iv[] =
      {
          0x06, 0xcc, 0x64, 0xe4, 0x03, 0xcc, 0xaa, 0x0c,
          0x56, 0x30, 0xa3, 0x72, 0xf2, 0x63, 0xe1, 0x9f};

  SharedPtr aes_alg_ptr{nullptr};
  DWORD key_object_size{0};
  DWORD block_length{0};

  BoolEither InitAes() noexcept;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_
