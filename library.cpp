#include "library.h"

SmarteamRepository *smarteam_repo_ptr;

BOOL DllMain(HINSTANCE, DWORD const reason, LPVOID) {
  switch (reason) {
    case DLL_PROCESS_ATTACH:
      std::cout << "DLL_PROCESS_ATTACH" << std::endl;
      CoInitialize(nullptr);
      break;

      //    case DLL_THREAD_ATTACH:
      //      break;

      //    case DLL_THREAD_DETACH:
      //      break;

    case DLL_PROCESS_DETACH:
      std::cout << "DLL_PROCESS_DETACH" << std::endl;
      CoUninitialize();
      break;

    default:
      break;
  }
  return TRUE;
}

EitherPod<bool> *Init() {
  std::cout << "Init" << std::endl;
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
  std::wcout << L"Username: " << username << std::endl;
  std::wcout << L"Password: " << password << std::endl;

  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);

  const auto login_either_ = user_gateway_.UserLogin(username, password);

  return login_either_.Fold(
      [](const auto left) { return new EitherPod<bool>{true, gateway_helper::PodFromException(left)}; },
      [](const auto right) {
        return new EitherPod<bool>{false, {}, right};
      });
}
