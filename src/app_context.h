//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_APP_CONTEXT_H_
#define SMART_COM_SRC_APP_CONTEXT_H_

#include <iostream>
#include <any>
#include <map>
#include <smarteam/gateways/pods/either_pod.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/gateways/helpers/geteway_helper.h>

class AppContext {
 private:
  SmarteamRepository *smarteam_repo_ptr {nullptr};

 public:
  AppContext() noexcept = default;

  virtual ~AppContext();

  EitherPod<bool> *Init() noexcept;

  EitherPod<bool> *Release() noexcept;
};

#endif//SMART_COM_SRC_APP_CONTEXT_H_
