//
// Created by nim on 07.09.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DOMAIN_USE_CASES_USER_USE_CASES_H_
#define SMART_COM_SRC_SMARTEAM_DOMAIN_USE_CASES_USER_USE_CASES_H_

#include <monad/either.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>

class UserUseCases {
 public:
  using BoolEither = monad::Either<std::exception, bool>;

  explicit UserUseCases(SmarteamRepository::SmarteamRepositoryPtr smarteam_repository) noexcept;

  virtual ~UserUseCases() noexcept;

  BoolEither UserLogoff() noexcept;

  BoolEither UserLogin(const wchar_t *username, const wchar_t *password) noexcept;

 private:
  SmarteamRepository::SmarteamRepositoryPtr smarteam_repository;
};

#endif//SMART_COM_SRC_SMARTEAM_DOMAIN_USE_CASES_USER_USE_CASES_H_
