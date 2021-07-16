//
// Created by nim on 15.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_H_
#define SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_H_

#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <sstream>
#include <windows.h>
#include <smarteam/use_cases/ports/repositories/ismarteam_repository.h>
#include <smarteam/data/providers/smarteam_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/session_provider.h>
#include <smarteam/data/pods/session_pod.h>

using namespace smarteam;

class SmarteamRepository: public ISmarteamRepository {
 public:
  using SmarteamRepoEither = monad::Either<std::exception, SmarteamRepository*>;
  using BoolEither = monad::Either<std::exception, bool>;

  static SmarteamRepoEither GetInstance();

  ~SmarteamRepository() override;

  BoolEither UserLoggedOn() override;

  BoolEither UserLogoff() override;

  BoolEither UserLogin(const _bstr_t& user_name, const _bstr_t& password) override;


  SmarteamRepository(const SmarteamRepository &) = delete;

  void operator=(const SmarteamRepository &) = delete;

 private:
  SessionProvider &session_provider;

  explicit SmarteamRepository(SessionProvider &session_provider);
};

#endif//SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_H_
