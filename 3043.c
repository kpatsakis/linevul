base::string16 GoogleChromeDistribution::GetDistributionData(HKEY root_key) {
  base::string16 sub_key(google_update::kRegPathClientState);
  sub_key.append(L"\\");
  sub_key.append(install_static::GetAppGuid());

  base::win::RegKey client_state_key(
      root_key, sub_key.c_str(), KEY_READ | KEY_WOW64_32KEY);
  base::string16 result;
  base::string16 brand_value;
  if (client_state_key.ReadValue(google_update::kRegRLZBrandField,
                                 &brand_value) == ERROR_SUCCESS) {
    result = google_update::kRegRLZBrandField;
    result.append(L"=");
    result.append(brand_value);
    result.append(L"&");
  }

  base::string16 client_value;
  if (client_state_key.ReadValue(google_update::kRegClientField,
                                 &client_value) == ERROR_SUCCESS) {
    result.append(google_update::kRegClientField);
    result.append(L"=");
    result.append(client_value);
    result.append(L"&");
  }

  base::string16 ap_value;
  client_state_key.ReadValue(google_update::kRegApField, &ap_value);
  result.append(google_update::kRegApField);
  result.append(L"=");
  result.append(ap_value);

  base::FilePath crash_dir;
  if (chrome::GetDefaultUserDataDirectory(&crash_dir)) {
    crash_dir = crash_dir.Append(FILE_PATH_LITERAL("Crashpad"));
    crashpad::UUID client_id;
    std::unique_ptr<crashpad::CrashReportDatabase> database(
        crashpad::CrashReportDatabase::InitializeWithoutCreating(crash_dir));
    if (database && database->GetSettings()->GetClientID(&client_id))
      result.append(L"&crash_client_id=").append(client_id.ToString16());
  }

  return result;
}
