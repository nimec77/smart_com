#include "library.h"

BOOL DllMain(HINSTANCE, DWORD const reason, LPVOID) {
  switch (reason) {
    case DLL_PROCESS_ATTACH:
      std::cout << "DLL_PROCESS_ATTACH" << std::endl;
      break;

    case DLL_THREAD_ATTACH:
      std::cout << "DLL_THREAD_ATTACH" << std::endl;
      break;

    case DLL_THREAD_DETACH:
      std::cout << "DLL_THREAD_DETACH" << std::endl;
      break;

    case DLL_PROCESS_DETACH:
      std::cout << "DLL_PROCESS_DETACH" << std::endl;
      break;

    default:
      break;
  }
  return TRUE;
}


AppContext *InitAppContext() {
  auto app_context_ = new AppContext();

  app_context_->Set(typeid(SmarteamGateway).name(), std::any(SmarteamGateway()));

  return app_context_;
}

EitherPod<bool> *Init() {
  if (app_context == nullptr) {
    app_context = InitAppContext();
  }

  auto smarteam_gateway_ = std::any_cast<SmarteamGateway>(app_context->Get(typeid(SmarteamGateway).name()));

  return smarteam_gateway_.Init();
}


EitherPod<bool> *Release() {
  auto smarteam_gateway_ = std::any_cast<SmarteamGateway>(app_context->Get(typeid(SmarteamGateway).name()));

  return smarteam_gateway_.Release();
}

EitherPod<bool> *RightTest() noexcept {
  std::cout << "RightTest" << std::endl;
  return new EitherPod<bool>{false, {}, true};
}

EitherPod<bool> *LeftTest() noexcept {
  std::cout << "LeftTest" << std::endl;

  const auto exception_pod_ = ExceptionPod{ExceptionType::kRuntimeError, "Runtime Error"};

  return new EitherPod<bool>{true, exception_pod_};
}
EitherPod<bool> *UserLogoff() {
  //  std::cout << "UserLogoff" << std::endl;
  //  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);
  //
  //  const auto is_logged_either_ = user_gateway_.UserLogoff();
  //
  //  return is_logged_either_.Fold(
  //      [](const auto left) {
  //        return new EitherPod<bool>{true, gateway_helper::PodFromException(left)};
  //      },
  //      [](const auto right) {
  //        return new EitherPod<bool>{false, {}, right};
  //      });
  return new EitherPod<bool>{false, {}, true};
}
EitherPod<bool> *UserLogin(const wchar_t *username, const wchar_t *password) {
  //  CoInitialize(nullptr);
  //  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);
  //
  //  const auto login_either_ = user_gateway_.UserLogin(username, password);
  //
  //  return login_either_.Fold(
  //      [](const auto left) { return new EitherPod<bool>{true, gateway_helper::PodFromException(left)}; },
  //      [](const auto right) {
  //        return new EitherPod<bool>{false, {}, right};
  //      });
  return new EitherPod<bool>{false, {}, true};
}
