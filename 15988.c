std::wstring DetermineChannel(const InstallConstants& mode,
                              bool system_level,
                              bool from_binaries,
                              std::wstring* update_ap,
                              std::wstring* update_cohort_name) {
  if (!kUseGoogleUpdateIntegration)
    return std::wstring();

  std::wstring client_state(from_binaries
                                ? GetBinariesClientStateKeyPath()
                                : GetClientStateKeyPath(mode.app_guid));
  std::wstring ap_value;
  nt::QueryRegValueSZ(system_level ? nt::HKLM : nt::HKCU, nt::WOW6432,
                      client_state.c_str(), kRegValueAp, &ap_value);
  if (update_ap)
    *update_ap = ap_value;

  if (update_cohort_name) {
    nt::QueryRegValueSZ(system_level ? nt::HKLM : nt::HKCU, nt::WOW6432,
                        client_state.append(L"\\cohort").c_str(), kRegValueName,
                        update_cohort_name);
  }

  switch (mode.channel_strategy) {
    case ChannelStrategy::UNSUPPORTED:
      assert(false);
      break;
    case ChannelStrategy::ADDITIONAL_PARAMETERS:
      return ChannelFromAdditionalParameters(mode, ap_value);
    case ChannelStrategy::FIXED:
      return mode.default_channel_name;
  }

  return std::wstring();
}
