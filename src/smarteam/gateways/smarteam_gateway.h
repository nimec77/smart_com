//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_SMARTEAM_GATEWAY_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_SMARTEAM_GATEWAY_H_

#include <iostream>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/domain/use_cases/ports/gateways/user_gateway.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/gateways/helpers/geteway_helper.h>
#include <smarteam/gateways/pods/either_pod.h>
#include <smarteam/gateways/user_gateway_imp.h>
#include <windows.h>

class SmarteamGateway {
 private:
  SmarteamRepository *smarteam_repo_ptr;

 public:
  EitherPod<bool> *Init() noexcept;

  EitherPod<bool> *Release() noexcept;

};

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_SMARTEAM_GATEWAY_H_
