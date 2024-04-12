scoped_ptr<ConfigurationPolicyHandlerList> BuildHandlerList(
    const Schema& chrome_schema) {
  scoped_ptr<ConfigurationPolicyHandlerList> handlers(
      new ConfigurationPolicyHandlerList(
          base::Bind(&PopulatePolicyHandlerParameters),
          base::Bind(&GetChromePolicyDetails)));
  for (size_t i = 0; i < arraysize(kSimplePolicyMap); ++i) {
    handlers->AddHandler(make_scoped_ptr(new SimplePolicyHandler(
        kSimplePolicyMap[i].policy_name, kSimplePolicyMap[i].preference_path,
        kSimplePolicyMap[i].value_type)));
  }

  handlers->AddHandler(make_scoped_ptr(new AutofillPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new DefaultSearchPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new ForceSafeSearchPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new IncognitoModePolicyHandler()));
  handlers->AddHandler(
      make_scoped_ptr(new ManagedBookmarksPolicyHandler(chrome_schema)));
  handlers->AddHandler(make_scoped_ptr(new ProxyPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new URLBlacklistPolicyHandler()));

#if defined(OS_ANDROID)
  handlers->AddHandler(
      make_scoped_ptr(new ContextualSearchPolicyHandlerAndroid()));
#endif

#if !defined(OS_IOS)
  handlers->AddHandler(
      make_scoped_ptr(new FileSelectionDialogsPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new JavascriptPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new NetworkPredictionPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new RestoreOnStartupPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new sync_driver::SyncPolicyHandler()));

  handlers->AddHandler(make_scoped_ptr(new StringMappingListPolicyHandler(
      key::kEnableDeprecatedWebPlatformFeatures,
      prefs::kEnableDeprecatedWebPlatformFeatures,
      base::Bind(GetDeprecatedFeaturesMap))));
#endif  // !defined(OS_IOS)

#if defined(ENABLE_EXTENSIONS)
  handlers->AddHandler(
      make_scoped_ptr(new extensions::ExtensionListPolicyHandler(
          key::kExtensionInstallWhitelist,
          extensions::pref_names::kInstallAllowList, false)));
  handlers->AddHandler(
      make_scoped_ptr(new extensions::ExtensionListPolicyHandler(
          key::kExtensionInstallBlacklist,
          extensions::pref_names::kInstallDenyList, true)));
  handlers->AddHandler(make_scoped_ptr(
      new extensions::ExtensionInstallForcelistPolicyHandler()));
  handlers->AddHandler(
      make_scoped_ptr(new extensions::ExtensionURLPatternListPolicyHandler(
          key::kExtensionInstallSources,
          extensions::pref_names::kAllowedInstallSites)));
  handlers->AddHandler(make_scoped_ptr(new StringMappingListPolicyHandler(
      key::kExtensionAllowedTypes, extensions::pref_names::kAllowedTypes,
      base::Bind(GetExtensionAllowedTypesMap))));
  handlers->AddHandler(make_scoped_ptr(
      new extensions::ExtensionSettingsPolicyHandler(chrome_schema)));
#endif

#if !defined(OS_CHROMEOS) && !defined(OS_ANDROID) && !defined(OS_IOS)
  handlers->AddHandler(make_scoped_ptr(new DiskCacheDirPolicyHandler()));

  handlers->AddHandler(
      make_scoped_ptr(new extensions::NativeMessagingHostListPolicyHandler(
          key::kNativeMessagingWhitelist,
          extensions::pref_names::kNativeMessagingWhitelist, false)));
  handlers->AddHandler(
      make_scoped_ptr(new extensions::NativeMessagingHostListPolicyHandler(
          key::kNativeMessagingBlacklist,
          extensions::pref_names::kNativeMessagingBlacklist, true)));
#endif  // !defined(OS_CHROMEOS) && !defined(OS_ANDROID) && !defined(OS_IOS)

#if !defined(OS_ANDROID) && !defined(OS_IOS)
  handlers->AddHandler(make_scoped_ptr(new DownloadDirPolicyHandler));

  handlers->AddHandler(make_scoped_ptr(new SimpleSchemaValidatingPolicyHandler(
      key::kRegisteredProtocolHandlers,
      prefs::kPolicyRegisteredProtocolHandlers, chrome_schema, SCHEMA_STRICT,
      SimpleSchemaValidatingPolicyHandler::RECOMMENDED_ALLOWED,
      SimpleSchemaValidatingPolicyHandler::MANDATORY_PROHIBITED)));
#endif

#if defined(OS_CHROMEOS)
  handlers->AddHandler(
      make_scoped_ptr(new extensions::ExtensionListPolicyHandler(
          key::kAttestationExtensionWhitelist,
          prefs::kAttestationExtensionWhitelist, false)));
  handlers->AddHandler(make_scoped_ptr(
      NetworkConfigurationPolicyHandler::CreateForDevicePolicy()));
  handlers->AddHandler(make_scoped_ptr(
      NetworkConfigurationPolicyHandler::CreateForUserPolicy()));
  handlers->AddHandler(make_scoped_ptr(new PinnedLauncherAppsPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(new ScreenMagnifierPolicyHandler()));
  handlers->AddHandler(make_scoped_ptr(
      new LoginScreenPowerManagementPolicyHandler(chrome_schema)));

  ScopedVector<ConfigurationPolicyHandler>
      power_management_idle_legacy_policies;
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenDimDelayAC,
                                prefs::kPowerAcScreenDimDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenOffDelayAC,
                                prefs::kPowerAcScreenOffDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kIdleWarningDelayAC,
                                prefs::kPowerAcIdleWarningDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(new IntRangePolicyHandler(
      key::kIdleDelayAC, prefs::kPowerAcIdleDelayMs, 0, INT_MAX, true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenDimDelayBattery,
                                prefs::kPowerBatteryScreenDimDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenOffDelayBattery,
                                prefs::kPowerBatteryScreenOffDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kIdleWarningDelayBattery,
                                prefs::kPowerBatteryIdleWarningDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kIdleDelayBattery,
                                prefs::kPowerBatteryIdleDelayMs,
                                0,
                                INT_MAX,
                                true));
  power_management_idle_legacy_policies.push_back(new IntRangePolicyHandler(
      key::kIdleActionAC,
      prefs::kPowerAcIdleAction,
      chromeos::PowerPolicyController::ACTION_SUSPEND,
      chromeos::PowerPolicyController::ACTION_DO_NOTHING,
      false));
  power_management_idle_legacy_policies.push_back(new IntRangePolicyHandler(
      key::kIdleActionBattery,
      prefs::kPowerBatteryIdleAction,
      chromeos::PowerPolicyController::ACTION_SUSPEND,
      chromeos::PowerPolicyController::ACTION_DO_NOTHING,
      false));
  power_management_idle_legacy_policies.push_back(
      new DeprecatedIdleActionHandler());

  ScopedVector<ConfigurationPolicyHandler> screen_lock_legacy_policies;
  screen_lock_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenLockDelayAC,
                                prefs::kPowerAcScreenLockDelayMs,
                                0,
                                INT_MAX,
                                true));
  screen_lock_legacy_policies.push_back(
      new IntRangePolicyHandler(key::kScreenLockDelayBattery,
                                prefs::kPowerBatteryScreenLockDelayMs,
                                0,
                                INT_MAX,
                                true));

  handlers->AddHandler(make_scoped_ptr(new IntRangePolicyHandler(
      key::kSAMLOfflineSigninTimeLimit, prefs::kSAMLOfflineSigninTimeLimit, -1,
      INT_MAX, true)));
  handlers->AddHandler(make_scoped_ptr(new IntRangePolicyHandler(
      key::kLidCloseAction, prefs::kPowerLidClosedAction,
      chromeos::PowerPolicyController::ACTION_SUSPEND,
      chromeos::PowerPolicyController::ACTION_DO_NOTHING, false)));
  handlers->AddHandler(make_scoped_ptr(new IntPercentageToDoublePolicyHandler(
      key::kPresentationScreenDimDelayScale,
      prefs::kPowerPresentationScreenDimDelayFactor, 100, INT_MAX, true)));
  handlers->AddHandler(make_scoped_ptr(new IntPercentageToDoublePolicyHandler(
      key::kUserActivityScreenDimDelayScale,
      prefs::kPowerUserActivityScreenDimDelayFactor, 100, INT_MAX, true)));
  handlers->AddHandler(make_scoped_ptr(new IntRangePolicyHandler(
      key::kUptimeLimit, prefs::kUptimeLimit, 3600, INT_MAX, true)));
  handlers->AddHandler(make_scoped_ptr(new IntRangePolicyHandler(
      key::kDeviceLoginScreenDefaultScreenMagnifierType, NULL, 0,
      ui::MAGNIFIER_FULL, false)));
  handlers->AddHandler(
      make_scoped_ptr(new LegacyPoliciesDeprecatingPolicyHandler(
          power_management_idle_legacy_policies.Pass(),
          make_scoped_ptr(
              new PowerManagementIdleSettingsPolicyHandler(chrome_schema)))));
  handlers->AddHandler(
      make_scoped_ptr(new LegacyPoliciesDeprecatingPolicyHandler(
          screen_lock_legacy_policies.Pass(),
          make_scoped_ptr(new ScreenLockDelayPolicyHandler(chrome_schema)))));
  handlers->AddHandler(
      make_scoped_ptr(new ExternalDataPolicyHandler(key::kUserAvatarImage)));
  handlers->AddHandler(
      make_scoped_ptr(new ExternalDataPolicyHandler(key::kWallpaperImage)));
  handlers->AddHandler(make_scoped_ptr(new SimpleSchemaValidatingPolicyHandler(
      key::kSessionLocales, NULL, chrome_schema, SCHEMA_STRICT,
      SimpleSchemaValidatingPolicyHandler::RECOMMENDED_ALLOWED,
      SimpleSchemaValidatingPolicyHandler::MANDATORY_PROHIBITED)));
  handlers->AddHandler(make_scoped_ptr(
      new chromeos::KeyPermissionsPolicyHandler(chrome_schema)));
#endif  // defined(OS_CHROMEOS)

  return handlers.Pass();
}
