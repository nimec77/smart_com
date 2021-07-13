//
// Created by nim on 13.07.2021.
//

#include "session_provider.h"

namespace smarteam {
using IDispatchEither = SessionProvider::IDispatchEither;

SessionProvider *session_provider_ptr{nullptr};

SessionProvider::SessionProvider(IDispatch &app) noexcept : session_app{app} {
  std::cout << "SessionProvider start" << std::endl;
}

SessionProvider::~SessionProvider() {
  std::cout << "~SessionProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &session_app);
  session_provider_ptr = nullptr;
}

SessionProvider *SessionProvider::GetInstance(IDispatch *app) noexcept {
  if (session_provider_ptr == nullptr) {
    session_provider_ptr = new SessionProvider(*app);
  }

  return session_provider_ptr;
}

}// namespace smarteam