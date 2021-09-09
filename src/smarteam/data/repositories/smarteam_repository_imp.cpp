//
// Created by nim on 15.07.2021.
//

#include "smarteam_repository_imp.h"

using SmarteamRepositoryPtr = SmarteamRepositoryImp::SmarteamRepositoryPtr;
using SmarteamRepoEither = SmarteamRepositoryImp::SmarteamRepoEither;

SmarteamRepositoryPtr smarteam_repository_ptr;

SmarteamRepositoryImp::SmarteamRepositoryImp(SessionProvider::SessionProviderPtr session_provider) noexcept
    : session_provider{std::move(session_provider)} {}

SmarteamRepositoryImp::~SmarteamRepositoryImp() noexcept {
  std::cout << "~SmarteamRepositoryImp" << std::endl;
  if (!smarteam_repository_ptr) {
    return;
  }
  SessionProvider::GetInstance().WhenRight([](SessionProvider::SessionProviderPtr session_provider_ptr) noexcept {
    session_provider_ptr.reset();
  });
  DatabaseProvider::GetInstance().WhenRight([](DatabaseProvider::DatabaseProviderPtr database_provider_ptr) noexcept {
    database_provider_ptr.reset();
  });
  EngineProvider::GetInstance().WhenRight([](EngineProvider::EngineProviderPtr engine_provider_ptr) noexcept {
    engine_provider_ptr.reset();
  });
  SmarteamProvider::GetInstance().WhenRight([](SmarteamProvider::SmarteamProviderPtr smarteam_provider_ptr) noexcept {
    smarteam_provider_ptr.reset();
  });
  smarteam_repository_ptr.reset();
}
SmarteamRepoEither SmarteamRepositoryImp::GetInstance() noexcept {
  if (smarteam_repository_ptr != nullptr) {
    return SmarteamRepoEither::RightOf(smarteam_repository_ptr);
  }

  return SmarteamProvider::GetInstance()
      .RightFlatMap([](const SmarteamProvider::SmarteamProviderPtr &smarteam_provider_ptr) noexcept {
        return smarteam_provider_ptr->GetEngine();
      })
      .RightFlatMap([](const auto engine_app) noexcept {
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
      .RightFlatMap([](const auto session_pod) noexcept {
        return session_pod.database_provider_ptr->GetAlias().RightMap([session_pod](const auto alias) {
          auto session_pod_ = SessionPod{session_pod};
          session_pod_.alias = alias;

          return session_pod_;
        });
      })
      .RightFlatMap([](const auto session_pod) noexcept {
        return session_pod.database_provider_ptr->GetPassword().RightMap([session_pod](const auto password) {
          auto session_pod_ = SessionPod{session_pod};
          session_pod_.database_password = password;

          return session_pod_;
        });
      })
      .RightFlatMap([](const auto session_pod) noexcept {
        const auto application_name_ = _bstr_t{kApplicationName};
        const auto configuration_name_ = _bstr_t{kConfigurationName};
        return session_pod.engine_provider_ptr->CreateSession(application_name_, configuration_name_)
            .RightMap([session_pod](const auto session_app) {
              auto session_pod_ = SessionPod{session_pod};
              session_pod_.session_provider_ptr = SessionProvider::GetInstance(session_app);

              return session_pod_;
            });
      })
      .RightFlatMap([](const auto session_pod) noexcept {
        return session_pod.session_provider_ptr->OpenDatabaseConnection(
                                                   session_pod.alias,
                                                   session_pod.database_password,
                                                   PasswordType::kEncoded)
            .RightMap([session_pod](const auto database_connection_app) {
              return SmarteamRepositoryPtr(new SmarteamRepositoryImp{session_pod.session_provider_ptr});
            });
      })
      .RightMap([](const auto smarteam_repository) noexcept {
        smarteam_repository_ptr = smarteam_repository;
        return smarteam_repository_ptr;
      });
}

BoolEither SmarteamRepositoryImp::UserLoggedOn() noexcept {
  return session_provider->UserLoggedOn();
}

BoolEither SmarteamRepositoryImp::UserLogoff() noexcept {
  return session_provider->UserLogoff();
}

BoolEither SmarteamRepositoryImp::UserLogin(const _bstr_t &user_name,
                                            const _bstr_t &password) noexcept {
  return session_provider->UserLogin(user_name, password);
}
