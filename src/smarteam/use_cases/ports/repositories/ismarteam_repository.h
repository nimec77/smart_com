//
// Created by nim on 15.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_
#define SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_

#include <monad/either.h>

class ISmarteamRepository {
  using BoolEither = monad::Either<std::exception, bool>;

 public:
  virtual ~ISmarteamRepository() {};

  virtual BoolEither UserLoggedOn() = 0;

  virtual BoolEither UserLogoff() = 0;

};

#endif//SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_
