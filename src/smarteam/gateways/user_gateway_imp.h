//
// Created by nim on 19.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_

#include <common/helpers/geteway_helper.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/domain/use_cases/ports/gateways/user_gateway.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/domain/use_cases/user_use_cases.h>

class UserGatewayImp : public UserGateway {
 public:

  explicit UserGatewayImp(const UserUseCases &user_use_case) noexcept;

  ~UserGatewayImp() noexcept override = default;

  EitherPod<bool> *UserLogoff() noexcept override;

  EitherPod<bool> *UserLogin(const wchar_t *username, const wchar_t *password) noexcept override;

 private:
  UserUseCases user_use_case;
};

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_USER_GATEWAY_IMP_H_
