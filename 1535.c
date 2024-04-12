bool AppListControllerDelegate::IsExtensionInstalled(
    Profile* profile, const std::string& app_id) {
  return !!GetExtension(profile, app_id);
}
