//
// Created by nim on 15.07.2021.
//

#include "smarteam_repository.h"

using SmarteamRepoEither = SmarteamRepository::SmarteamRepoEither;
using SeesionPodEither = SmarteamRepository::SessionPodEither;

SmarteamRepository *smarteam_repository_ptr{nullptr};

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

  return SmarteamProvider::GetInstance()
      .RightFlatMap([](const auto smarteam_provider_ptr) {
        return smarteam_provider_ptr->GetEngine();
      })
      .RightFlatMap([](const auto engine_app) {
        const auto engine_provider_ptr = EngineProvider::GetInstance(engine_app);
        auto session_pod = SessionPod{engine_provider_ptr};
        return engine_provider_ptr->GetDatabase(0)
            .RightMap([session_pod](const auto database_app) {
              auto database_provider_ptr = DatabaseProvider::GetInstance(database_app);
              auto new_session_pod = SessionPod{session_pod};
              new_session_pod.database_provider_ptr = database_provider_ptr;

              return new_session_pod;
            });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.database_provider_ptr->GetAlias().RightMap([session_pod](const auto alias) {
          auto new_session_pod = SessionPod{session_pod};
          new_session_pod.alias = alias;

          return new_session_pod;
        });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.database_provider_ptr->GetPassword().RightMap([session_pod](const auto password) {
          auto new_session_pod = SessionPod{session_pod};
          new_session_pod.database_password = password;

          return new_session_pod;
        });
      })
      .RightFlatMap([](const auto session_pod) {
        const auto application_name = _bstr_t{kApplicationName};
        const auto configuration_name = _bstr_t{kConfigurationName};
        return session_pod.engine_provider_ptr->CreateSession(application_name, configuration_name)
            .RightMap([session_pod](const auto session_app) {
              auto new_session_pod = SessionPod{session_pod};
              new_session_pod.session_provider_ptr = SessionProvider::GetInstance(session_app);

              return new_session_pod;
            });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.session_provider_ptr->OpenDatabaseConnection(session_pod.alias, session_pod.database_password, true)
            .RightMap([session_pod](const auto database_connection_app) {
              return new SmarteamRepository{*session_pod.session_provider_ptr};
            });
      })
      .RightMap([](const auto smarteam_repository) {
        smarteam_repository_ptr = smarteam_repository;
        return smarteam_repository_ptr;
      });
}
