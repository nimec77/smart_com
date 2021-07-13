//
// Created by nim on 13.07.2021.
//

#include "engine_provider.h"

namespace smarteam {
using EngineEither = EngineProvider::EngineEither;

EngineProvider *engine_provider_ptr = nullptr;

EngineProvider::EngineProvider(IDispatch &app) : engine_app{app} {
  std::cout << "EngineProvider start" << std::endl;
}

EngineProvider::~EngineProvider() {
  std::cout << "~EngineProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &engine_app);
  engine_provider_ptr = nullptr;
}

EngineEither EngineProvider::GetInstance(IDispatch *app) {
  std::cout << "EngineProvider::GetInstance start" << std::endl;
  if (engine_provider_ptr == nullptr) {
    engine_provider_ptr = new EngineProvider(*app);
  }

  return EngineEither::RightOf(engine_provider_ptr);
}

}// namespace smarteam