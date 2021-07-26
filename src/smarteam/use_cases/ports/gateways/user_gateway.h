//
// Created by nim on 19.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_
#define SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_

#include <monad/either.h>

class UserGateway {
 public:
  using BoolEither = monad::Either<std::exception, bool>;

  virtual ~UserGateway() = default;

  virtual BoolEither UserLogoff() = 0;

  virtual BoolEither UserLogin(const char* user_name, const char* password) = 0;

};
#endif//SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_GATEWAYS_USER_GATEWAY_H_
