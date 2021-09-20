//
// Created by nim on 06.09.2021.
//

#include "app_context.h"

#include <memory>

AppContext::~AppContext() {
  Release();
}

EitherPod<bool> *AppContext::Init() noexcept {
  std::cout << "AppContext::Init" << std::endl;
  if (initialized) {
    std::cout << "Already initialized, skipped" << std::endl;
    return new EitherPod<bool>{false, {}, true};
  }
  CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
  return SmarteamRepositoryImp::GetInstance().Fold(
      [](const auto exception) noexcept {
        const auto left_ = gateway_helper::PodFromException(exception);

        return new EitherPod<bool>{true, left_};
      },
      [this](auto smarteam_repo) noexcept {
        CreateGateways(smarteam_repo);
        return new EitherPod<bool>{false, {}, true};
      });
}

void AppContext::CreateGateways(SmarteamRepository::SmarteamRepositoryPtr &smarteam_repository_ptr) noexcept {
  const auto user_use_cases_ = UserUseCases(smarteam_repository_ptr);
  user_gateway_ptr = UserGateway::UserGatewayPtr{new UserGatewayImp(user_use_cases_)};

  const auto sid_provider_ptr_ = SidProvider::SidProviderPtr{new SidProviderImp()};
  const auto crypto_provider_ptr_ = CryptoProvider::CryptoProviderPtr{new CryptoProviderImp()};
  const auto crypto_repository_ptr_ = CryptoRepository::CryptoRepositoryPtr{
    new CryptoRepositoryImp(sid_provider_ptr_,
                            crypto_provider_ptr_)};
  const auto crypt_use_cases_ = std::make_shared<CryptoUseCases>(crypto_repository_ptr_);
  crypto_gateway_ptr = CryptoGateway::CryptoGatewayPtr{new CryptoGatewayImp{*crypt_use_cases_}};

}


EitherPod<bool> *AppContext::Release() noexcept {
  std::cout << "AppContext::Release" << std::endl;
  crypto_gateway_ptr.reset();
  user_gateway_ptr.reset();
  CoUninitialize();
  initialized = false;
  return new EitherPod<bool>{false, {}, true};
}

UserGateway *AppContext::GetUserGateway() noexcept {
  return user_gateway_ptr.get();
}

CryptoGateway *AppContext::GetCryptoGateway() noexcept {
  return crypto_gateway_ptr.get();
}
