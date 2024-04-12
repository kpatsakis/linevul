LogoServiceFactory* LogoServiceFactory::GetInstance() {
  return base::Singleton<LogoServiceFactory>::get();
}
