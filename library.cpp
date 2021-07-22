#include "library.h"

SmarteamRepository *smarteam_repo_ptr;

BOOL DllMain(HINSTANCE, DWORD const reason, LPVOID) {
  switch (reason) {
    case DLL_PROCESS_ATTACH:
      CoInitialize(nullptr);
      break;

      //    case DLL_THREAD_ATTACH:
      //      break;

      //    case DLL_THREAD_DETACH:
      //      break;

    case DLL_PROCESS_DETACH:
      CoUninitialize();
      break;

    default:
      break;
  }
  return TRUE;
}

EitherPod<bool> *Init() {
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

  return new EitherPod<bool>{false, {}, true};
}


EitherPod<bool> *LeftTest() {
  const auto exception_pod_ = ExceptionPod{ExceptionType::kRuntimeError, "Runtime Error"};

  return new EitherPod<bool>{true, exception_pod_};
}
