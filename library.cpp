#include "library.h"

SmarteamRepository *smarteam_repo_ptr;

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

EitherPod<bool> *Init() {
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
      [](const auto smarteam_repo) {
        smarteam_repo_ptr = smarteam_repo;

        return new EitherPod<bool>{false, {}, true};
      });
}

EitherPod<bool> *Release() {
  std::cout << "Close" << std::endl;
  if (smarteam_repo_ptr != nullptr) {
    smarteam_repo_ptr->~SmarteamRepository();
  }
  smarteam_repo_ptr = nullptr;
  CoUninitialize();
  return new EitherPod<bool>{false, {}, true};
}

EitherPod<bool> *RightTest() {
  std::cout << "RightTest" << std::endl;
  return new EitherPod<bool>{false, {}, true};
}

EitherPod<bool> *LeftTest() {
  std::cout << "LeftTest" << std::endl;

  const auto exception_pod_ = ExceptionPod{ExceptionType::kRuntimeError, "Runtime Error"};

  return new EitherPod<bool>{true, exception_pod_};
}
EitherPod<bool> *UserLogoff() {
  std::cout << "UserLogoff" << std::endl;
  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);

  const auto is_logged_either_ = user_gateway_.UserLogoff();

  return is_logged_either_.Fold(
      [](const auto left) {
        return new EitherPod<bool>{true, gateway_helper::PodFromException(left)};
      },
      [](const auto right) {
        return new EitherPod<bool>{false, {}, right};
      });
}
EitherPod<bool> *UserLogin(const wchar_t *username, const wchar_t *password) {
  CoInitialize(nullptr);
  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);

  const auto login_either_ = user_gateway_.UserLogin(username, password);

  return login_either_.Fold(
      [](const auto left) { return new EitherPod<bool>{true, gateway_helper::PodFromException(left)}; },
      [](const auto right) {
        return new EitherPod<bool>{false, {}, right};
      });
}
