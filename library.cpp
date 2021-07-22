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

EitherPod<bool> *init() {
  return SmarteamRepositoryImp::GetInstance().Fold(
      [](const auto exception) {
        const auto message_ = exception.what();
        const auto left_ = ExceptionPod{ExceptionType::kException, message_};

        return new EitherPod<bool>{true, left_};
      },
      [](const auto smarteam_repo) {
        smarteam_repo_ptr = smarteam_repo;

        return new EitherPod<bool>{false, {}, true};
      });
}
