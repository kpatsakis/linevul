bool SkipConditionalFeatureEntry(const FeatureEntry& entry) {
  version_info::Channel channel = chrome::GetChannel();
#if defined(OS_ANDROID)
  if (!strcmp("enable-data-reduction-proxy-dev", entry.internal_name) &&
      channel != version_info::Channel::BETA &&
      channel != version_info::Channel::DEV) {
    return true;
  }
  if (!strcmp("enable-data-reduction-proxy-alt", entry.internal_name) &&
      channel != version_info::Channel::DEV) {
    return true;
  }
  if (!strcmp("enable-data-reduction-proxy-carrier-test",
              entry.internal_name) &&
      channel != version_info::Channel::DEV &&
      channel != version_info::Channel::CANARY &&
      channel != version_info::Channel::UNKNOWN) {
    return true;
  }
#endif

  if ((!strcmp("data-reduction-proxy-lo-fi", entry.internal_name) ||
       !strcmp("enable-data-reduction-proxy-lo-fi-preview",
               entry.internal_name)) &&
      channel != version_info::Channel::BETA &&
      channel != version_info::Channel::DEV &&
      channel != version_info::Channel::CANARY &&
      channel != version_info::Channel::UNKNOWN) {
    return true;
  }

  return false;
}
