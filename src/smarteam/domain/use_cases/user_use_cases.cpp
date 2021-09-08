//
// Created by nim on 07.09.2021.
//

#include "user_use_cases.h"

using BoolEither = UserUseCases::BoolEither;

UserUseCases::UserUseCases(SmarteamRepository::SmarteamRepositoryPtr smarteam_repository) noexcept
    : smarteam_repository{std::move(smarteam_repository)} {}

UserUseCases::~UserUseCases() noexcept {
  smarteam_repository.reset();
}

BoolEither UserUseCases::UserLogoff() noexcept {
  return smarteam_repository->UserLoggedOn()
      .RightFlatMap([this](const auto is_user_logged_on) noexcept {
        return is_user_logged_on ? smarteam_repository->UserLogoff() : BoolEither::RightOf(true);
      });
}

BoolEither UserUseCases::UserLogin(const wchar_t *username, const wchar_t *password) noexcept {
  return smarteam_repository->UserLogin(_bstr_t{username}, _bstr_t{password});
}
