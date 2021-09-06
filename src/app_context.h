//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_APP_CONTEXT_H_
#define SMART_COM_SRC_APP_CONTEXT_H_

#include <map>
#include <any>
#include <smarteam/gateways/smarteam_gateway.h>

using ContextMap = std::map<const char*, std::any>;

class AppContext {
 private:
  ContextMap context_map {};

 public:

  void Init();

  std::any Get(const char *type_name);

  std::any Set(const char *type_name, std::any object);

  [[nodiscard]] std::size_t Size() const noexcept;

};

#endif//SMART_COM_SRC_APP_CONTEXT_H_
