extensions::AppSorting* GetAppSorting(Profile* profile) {
  return extensions::ExtensionPrefs::Get(profile)->app_sorting();
}
