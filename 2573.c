void GetSanitizedEnabledFlagsForCurrentPlatform(
    FlagsStorage* flags_storage, std::set<std::string>* result) {
  GetSanitizedEnabledFlags(flags_storage, result);

  std::set<std::string> platform_experiments;
  int current_platform = GetCurrentPlatform();
  for (size_t i = 0; i < num_experiments; ++i) {
    if (experiments[i].supported_platforms & current_platform)
      AddInternalName(experiments[i], &platform_experiments);
#if defined(OS_CHROMEOS)
    if (experiments[i].supported_platforms & kOsCrOSOwnerOnly)
      AddInternalName(experiments[i], &platform_experiments);
#endif
  }

  std::set<std::string> new_enabled_experiments;
  std::set_intersection(
      platform_experiments.begin(), platform_experiments.end(),
      result->begin(), result->end(),
      std::inserter(new_enabled_experiments, new_enabled_experiments.begin()));

  result->swap(new_enabled_experiments);
}
