PlatformSensorProviderLinux* PlatformSensorProviderLinux::GetInstance() {
  return base::Singleton<
      PlatformSensorProviderLinux,
      base::LeakySingletonTraits<PlatformSensorProviderLinux>>::get();
}
