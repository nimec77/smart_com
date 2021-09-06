//
// Created by nim on 06.09.2021.
//

#include "app_context.h"

void AppContext::Init() {
  //TODO: Сделать создание объектов
}

std::any AppContext::Get(const char *type_name) {
  return context_map[type_name];
}

std::any AppContext::Set(const char *type_name, std::any object) {
  return context_map[type_name] = std::move(object);
}

std::size_t AppContext::Size() const noexcept {
  return context_map.size();
}
