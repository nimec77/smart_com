//
// Created by nim on 19.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_

#include <smarteam/use_cases/ports/gateways/user_gateway.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/use_cases/ports/repositories/smarteam_repository.h>
#include <comutil.h>

class UserGatewayImp: public UserGateway {
 public:
  using BooEither = UserGateway::BoolEither;

  explicit UserGatewayImp(SmarteamRepository& smarteam_repository);

  ~UserGatewayImp() override = default;

  BoolEither UserLogoff() override;

  BoolEither UserLogin(const wchar_t* user_name, const wchar_t * password) override;

 private:
  SmarteamRepository &smarteam_repository;
};

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_
