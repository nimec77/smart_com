//
// Created by nim on 15.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_IMP_H_
#define SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_IMP_H_

#include <iostream>
#include <common/base_types.h>
#include <memory>
#include <smarteam/constatns.h>
#include <smarteam/data/pods/session_pod.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/session_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <sstream>
#include <windows.h>

using namespace smarteam;

class SmarteamRepositoryImp: public SmarteamRepository {
 public:
  using SmarteamRepoEither = monad::Either<std::exception, SmarteamRepositoryPtr>;

  static SmarteamRepoEither GetInstance() noexcept ;

  ~SmarteamRepositoryImp() noexcept override;

  BoolEither UserLoggedOn() noexcept override;

  BoolEither UserLogoff() noexcept override;

  BoolEither UserLogin(const _bstr_t& user_name, const _bstr_t& password) noexcept override;


  SmarteamRepositoryImp(const SmarteamRepositoryImp &) = delete;

  void operator=(const SmarteamRepositoryImp &) = delete;

 private:
  SessionProvider::SessionProviderPtr session_provider;

  explicit SmarteamRepositoryImp(SessionProvider::SessionProviderPtr session_provider) noexcept;
};

#endif//SMART_COM_SRC_SMARTEAM_DATA_REPOSITORIES_SMARTEAM_REPOSITORY_IMP_H_
