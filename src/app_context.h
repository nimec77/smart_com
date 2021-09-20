//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_APP_CONTEXT_H_
#define SMART_COM_SRC_APP_CONTEXT_H_

#include <any>
#include <common/helpers/geteway_helper.h>
#include <common/pods/either_pod.h>
#include <iostream>
#include <map>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/domain/use_cases/ports/gateways/user_gateway.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/gateways/user_gateway_imp.h>
#include <crypto/gateways/crypto_gateway_imp.h>
#include <crypto/data/providers/sid_provider_imp.h>
#include <crypto/data/providers/crypto_provider_imp.h>
#include <crypto/data/repositories/crypto_repository_imp.h>
#include <crypto/domain/use_cases/crypto_use_cases.h>

class AppContext {
 public:
  AppContext() noexcept = default;

  virtual ~AppContext();

  EitherPod<bool> *Init() noexcept;

  EitherPod<bool> *Release() noexcept;

  UserGateway *GetUserGateway() noexcept;

  CryptoGateway *GetCryptoGateway() noexcept;

 protected:
  void CreateGateways(SmarteamRepository::SmarteamRepositoryPtr& smarteam_repository_ptr) noexcept;

 private:
  bool initialized {false};
  UserGateway::UserGatewayPtr user_gateway_ptr;
  CryptoGateway::CryptoGatewayPtr crypto_gateway_ptr;
};

#endif//SMART_COM_SRC_APP_CONTEXT_H_
