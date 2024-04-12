void DevToolsUIBindings::DevicesDiscoveryConfigUpdated() {
  CallClientFunction(
      "DevToolsAPI.devicesDiscoveryConfigChanged",
      profile_->GetPrefs()->FindPreference(
          prefs::kDevToolsDiscoverUsbDevicesEnabled)->GetValue(),
      profile_->GetPrefs()->FindPreference(
          prefs::kDevToolsPortForwardingEnabled)->GetValue(),
      profile_->GetPrefs()->FindPreference(
          prefs::kDevToolsPortForwardingConfig)->GetValue());
}
