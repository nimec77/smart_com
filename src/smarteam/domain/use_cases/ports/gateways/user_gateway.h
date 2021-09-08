//
// Created by nim on 19.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_
#define SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_

#include <monad/either.h>
#include <smarteam/gateways/pods/either_pod.h>

class UserGateway {
 public:
  virtual ~UserGateway() noexcept = default;

  virtual EitherPod<bool> *UserLogoff() noexcept = 0;

  virtual EitherPod<bool> *UserLogin(const wchar_t *user_name, const wchar_t *password) noexcept = 0;
};
#endif//SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_
