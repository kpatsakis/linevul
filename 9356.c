void AddLocalizedStrings(content::WebUIDataSource* html_source,
                         Profile* profile) {
  AddA11yStrings(html_source);
  AddAboutStrings(html_source);
  AddAppearanceStrings(html_source, profile);

#if defined(OS_WIN) && defined(GOOGLE_CHROME_BUILD)
  AddChromeCleanupStrings(html_source);
  AddIncompatibleApplicationsStrings(html_source);
#endif  // defined(OS_WIN) && defined(GOOGLE_CHROME_BUILD)

  AddChangePasswordStrings(html_source);
  AddClearBrowsingDataStrings(html_source, profile);
  AddCommonStrings(html_source, profile);
  AddDownloadsStrings(html_source);
  AddLanguagesStrings(html_source);
  AddOnStartupStrings(html_source);
  AddPasswordsAndFormsStrings(html_source);
  AddPeopleStrings(html_source, profile);
  AddPrintingStrings(html_source);
  AddPrivacyStrings(html_source, profile);
  AddResetStrings(html_source);
  AddSearchEnginesStrings(html_source);
#if defined(OS_CHROMEOS)
  AddGoogleAssistantStrings(html_source);
#endif
  AddSearchInSettingsStrings(html_source);
  AddSearchStrings(html_source, profile);
  AddSiteSettingsStrings(html_source, profile);
  AddWebContentStrings(html_source);

#if defined(OS_CHROMEOS)
  AddAndroidAppStrings(html_source);
  AddBluetoothStrings(html_source);
  AddChromeOSUserStrings(html_source, profile);
  AddDateTimeStrings(html_source);
  AddDeviceStrings(html_source);
  AddEasyUnlockStrings(html_source);
  AddInternetStrings(html_source);
  AddMultideviceStrings(html_source);
  AddUsersStrings(html_source);
#else
  AddDefaultBrowserStrings(html_source);
  AddImportDataStrings(html_source);
  AddSystemStrings(html_source);
#endif

#if defined(USE_NSS_CERTS)
  certificate_manager::AddLocalizedStrings(html_source);
#endif

#if defined(OS_CHROMEOS)
  chromeos::network_element::AddLocalizedStrings(html_source);
  chromeos::network_element::AddOncLocalizedStrings(html_source);
  chromeos::network_element::AddDetailsLocalizedStrings(html_source);
  chromeos::network_element::AddConfigLocalizedStrings(html_source);
  chromeos::network_element::AddErrorLocalizedStrings(html_source);
#endif
  policy_indicator::AddLocalizedStrings(html_source);

  html_source->SetJsonPath(kLocalizedStringsFile);
}
