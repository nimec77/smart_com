//
// Created by nim on 15.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_
#define SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_

#include <comutil.h>
#include <monad/either.h>

class SmarteamRepository {
 public:
  using BoolEither = monad::Either<std::exception, bool>;

  virtual ~SmarteamRepository() noexcept = default;

  virtual BoolEither UserLoggedOn() noexcept = 0;

  virtual BoolEither UserLogoff() noexcept = 0;

  virtual BoolEither UserLogin(const _bstr_t& user_name, const _bstr_t& password) noexcept = 0;

};

#endif//SMART_COM_SRC_SMARTEAM_USE_CASES_PORTS_REPOSITORIES_SMARTEAM_REPOSITORY_H_
