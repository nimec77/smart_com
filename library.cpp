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

EitherPod<bool> *Init() noexcept {
  return app_context.Init();
}

EitherPod<bool> *Release() noexcept {
  return app_context.Release();
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

EitherPod<bool> *UserLogoff() noexcept {
  return app_context.GetUserGateway()->UserLogoff();
}

EitherPod<bool> *UserLogin(const wchar_t *username, const wchar_t *password) noexcept {
  return app_context.GetUserGateway()->UserLogin(username, password);
}

EitherPod<const char *> *GetSid() noexcept {
  return app_context.GetCryptoGateway()->GetSid();
}

EitherPod<const char *> *Encode(const wchar_t *text) noexcept {
  return app_context.GetCryptoGateway()->Encode(text);
}

EitherPod<const char *> *Decode(const wchar_t *hex_text) noexcept {
  return app_context.GetCryptoGateway()->Decode(hex_text);
}