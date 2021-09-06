//
// Created by nim on 06.09.2021.
//

#include "smarteam_gateway.h"

EitherPod<bool> *SmarteamGateway::Init() noexcept {
  std::cout << "Init" << std::endl;
  if (smarteam_repo_ptr != nullptr) {
    std::cout << "Already initialized, skipped" << std::endl;
    return new EitherPod<bool>{false, {}, true};
  }
  CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
  return SmarteamRepositoryImp::GetInstance().Fold(
      [](const auto exception) {
        const auto left_ = gateway_helper::PodFromException(exception);

        return new EitherPod<bool>{true, left_};
        },
        [this](const auto smarteam_repo) {
        smarteam_repo_ptr = smarteam_repo;

        return new EitherPod<bool>{false, {}, true};
      });
}


EitherPod<bool> *SmarteamGateway::Release() noexcept {
  std::cout << "Close" << std::endl;
  if (smarteam_repo_ptr != nullptr) {
    smarteam_repo_ptr->~SmarteamRepository();
  }
  smarteam_repo_ptr = nullptr;
  CoUninitialize();
  return new EitherPod<bool>{false, {}, true};
}
