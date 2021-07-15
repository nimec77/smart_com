//
// Created by nim on 15.07.2021.
//

#include "smarteam_repository.h"

using SmarteamRepoEither = SmarteamRepository::SmarteamRepoEither;

SmarteamRepository *smarteam_repository_ptr{nullptr};
SessionPod session_pod{};

SmarteamRepository::SmarteamRepository(SessionProvider &session_provider) : session_provider(session_provider) {
  std::cout << "SmarteamRepository start" << std::endl;
}

SmarteamRepository::~SmarteamRepository() {
  std::cout << "~SmarteamRepository start" << std::endl;
  smarteam_repository_ptr = nullptr;
}
SmarteamRepoEither SmarteamRepository::GetInstance() {
  if (smarteam_repository_ptr != nullptr) {
    return SmarteamRepoEither::RightOf(smarteam_repository_ptr);
  }

  SmarteamProvider::GetInstance()
      .RightFlatMap([](const auto smarteam_provider_ptr) {
        return smarteam_provider_ptr->GetEngine();
      })
      .RightMap([](const auto engine_app) {
        return EngineProvider::GetInstance(engine_app);
      })
      .RightFlatMap([](const auto engine_provider_ptr) {
        session_pod.engine_provider_ptr = engine_provider_ptr;

        return engine_provider_ptr->GetDatabase(0);
      })
      .RightMap([](const auto database_app) {
        return DatabaseProvider::GetInstance(database_app);
      })
      .RightFlatMap([](const auto database_provider_ptr) {
        session_pod.database_provider_ptr = database_provider_ptr;

        return database_provider_ptr->GetAlias();
      });
  return SmarteamRepoEither::LeftOf(std::runtime_error("Not implemented"));
}
