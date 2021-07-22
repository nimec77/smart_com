//
// Created by nim on 22.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EITHER_POD_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EITHER_POD_H_

#include "exception_pod.h"

template<typename T>
struct EitherPod {
  const bool is_left;
  const ExceptionPod left;
  const T right;
};

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EITHER_POD_H_
