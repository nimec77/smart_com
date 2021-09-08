//
// Created by nim on 06.09.2021.
//

#include "app_context.h"

AppContext::~AppContext() {
  Release();
}

EitherPod<bool> *AppContext::Init() noexcept {
  std::cout << "AppContext::Init" << std::endl;
  if (smarteam_repo_ptr) {
    std::cout << "Already initialized, skipped" << std::endl;
    return new EitherPod<bool>{false, {}, true};
  }
  CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
  return SmarteamRepositoryImp::GetInstance().Fold(
      [](const auto exception) noexcept {
        const auto left_ = gateway_helper::PodFromException(exception);

        return new EitherPod<bool>{true, left_};
      },
      [this](const auto smarteam_repo) noexcept {
        smarteam_repo_ptr = smarteam_repo;
        return new EitherPod<bool>{false, {}, true};
      });
}

EitherPod<bool> *AppContext::Release() noexcept {
  std::cout << "AppContext::Release" << std::endl;
  if (smarteam_repo_ptr) {
    smarteam_repo_ptr.reset();
  }
  CoUninitialize();
  return new EitherPod<bool>{false, {}, true};
}
UserGateway *AppContext::GetUserGateway() noexcept {

  const auto user_use_cases_ = UserUseCases(smarteam_repo_ptr);
  return new UserGatewayImp(user_use_cases_);
}
