bool DocumentLoader::ShouldPersistUserGestureValue(
    const SecurityOrigin* previous_security_origin,
    const SecurityOrigin* new_security_origin) {
  if (!CheckOriginIsHttpOrHttps(previous_security_origin) ||
      !CheckOriginIsHttpOrHttps(new_security_origin))
    return false;

  if (previous_security_origin->Host() == new_security_origin->Host())
    return true;

  String previous_domain = NetworkUtils::GetDomainAndRegistry(
      previous_security_origin->Host(),
      NetworkUtils::kIncludePrivateRegistries);
  String new_domain = NetworkUtils::GetDomainAndRegistry(
      new_security_origin->Host(), NetworkUtils::kIncludePrivateRegistries);

  return !previous_domain.IsEmpty() && previous_domain == new_domain;
}
