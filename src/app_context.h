//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_APP_CONTEXT_H_
#define SMART_COM_SRC_APP_CONTEXT_H_

#include <any>
#include <iostream>
#include <map>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/domain/use_cases/ports/gateways/user_gateway.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/gateways/helpers/geteway_helper.h>
#include <smarteam/gateways/pods/either_pod.h>
#include <smarteam/gateways/user_gateway_imp.h>

class AppContext {
 private:
  SmarteamRepository *smarteam_repo_ptr {nullptr};

 public:
  AppContext() noexcept = default;

  virtual ~AppContext();

  EitherPod<bool> *Init() noexcept;

  EitherPod<bool> *Release() noexcept;

  UserGateway *GetUserGateway() noexcept;

};

#endif//SMART_COM_SRC_APP_CONTEXT_H_
