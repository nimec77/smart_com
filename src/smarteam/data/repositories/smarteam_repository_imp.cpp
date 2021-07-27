//
// Created by nim on 15.07.2021.
//

#include "smarteam_repository_imp.h"

using SmarteamRepoEither = SmarteamRepositoryImp::SmarteamRepoEither;
using BoolEither = SmarteamRepository::BoolEither;

SmarteamRepositoryImp *smarteam_repository_ptr{};

SmarteamRepositoryImp::SmarteamRepositoryImp(SessionProvider &session_provider) : session_provider(session_provider) {}

SmarteamRepositoryImp::~SmarteamRepositoryImp() {
  std::cout << "~SmarteamRepositoryImp" << std::endl;
  if (smarteam_repository_ptr == nullptr) {
    return;
  }
  SessionProvider::GetInstance().WhenRight([](const auto session_provider_ptr) {
    session_provider_ptr->~SessionProvider();
  });
  DatabaseProvider::GetInstance().WhenRight([](const auto database_provider_ptr) {
    database_provider_ptr->~DatabaseProvider();
  });
  EngineProvider::GetInstance().WhenRight([](const auto engine_provider_ptr) {
    engine_provider_ptr->~EngineProvider();
  });
  SmarteamProvider::GetInstance().WhenRight([](const auto smarteam_provider_ptr) {
    smarteam_provider_ptr->~SmarteamProvider();
  });
  smarteam_repository_ptr = nullptr;
}
SmarteamRepoEither SmarteamRepositoryImp::GetInstance() {
  if (smarteam_repository_ptr != nullptr) {
    return SmarteamRepoEither::RightOf(smarteam_repository_ptr);
  }

  return SmarteamProvider::GetInstance()
      .RightFlatMap([](const auto smarteam_provider_ptr) {
        return smarteam_provider_ptr->GetEngine();
      })
      .RightFlatMap([](const auto engine_app) {
        const auto engine_provider_ptr_ = EngineProvider::GetInstance(engine_app);
        const auto session_pod = SessionPod{engine_provider_ptr_};
        return engine_provider_ptr_->GetDatabase(0)
            .RightMap([session_pod](const auto database_app) {
              const auto database_provider_ptr_ = DatabaseProvider::GetInstance(database_app);
              auto session_pod_ = SessionPod{session_pod};
              session_pod_.database_provider_ptr = database_provider_ptr_;

              return session_pod_;
            });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.database_provider_ptr->GetAlias().RightMap([session_pod](const auto alias) {
          auto session_pod_ = SessionPod{session_pod};
          session_pod_.alias = alias;

          return session_pod_;
        });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.database_provider_ptr->GetPassword().RightMap([session_pod](const auto password) {
          auto session_pod_ = SessionPod{session_pod};
          session_pod_.database_password = password;

          return session_pod_;
        });
      })
      .RightFlatMap([](const auto session_pod) {
        const auto application_name_ = _bstr_t{kApplicationName};
        const auto configuration_name_ = _bstr_t{kConfigurationName};
        return session_pod.engine_provider_ptr->CreateSession(application_name_, configuration_name_)
            .RightMap([session_pod](const auto session_app) {
              auto session_pod_ = SessionPod{session_pod};
              session_pod_.session_provider_ptr = SessionProvider::GetInstance(session_app);

              return session_pod_;
            });
      })
      .RightFlatMap([](const auto session_pod) {
        return session_pod.session_provider_ptr->OpenDatabaseConnection(
                                                   session_pod.alias,
                                                   session_pod.database_password,
                                                   PasswordType::kEncoded)
            .RightMap([session_pod](const auto database_connection_app) {
              return new SmarteamRepositoryImp{*session_pod.session_provider_ptr};
            });
      })
      .RightMap([](const auto smarteam_repository) {
        smarteam_repository_ptr = smarteam_repository;
        return smarteam_repository_ptr;
      });
}

BoolEither SmarteamRepositoryImp::UserLoggedOn() {
  return session_provider.UserLoggedOn();
}

BoolEither SmarteamRepositoryImp::UserLogoff() {
  return session_provider.UserLogoff();
}

BoolEither SmarteamRepositoryImp::UserLogin(const _bstr_t &user_name, const _bstr_t &password) {
  //  std::cout << "SmarteamRepositoryImp: " << (helper::Utf16ToUtf8(user_name) | "Convert error!") << std::endl;
  return session_provider.UserLogin(user_name, password);
}
