std::string AppListControllerDelegate::AppListSourceToString(
    AppListSource source) {
  switch (source) {
    case LAUNCH_FROM_APP_LIST:
      return extension_urls::kLaunchSourceAppList;
    case LAUNCH_FROM_APP_LIST_SEARCH:
      return extension_urls::kLaunchSourceAppListSearch;
    default:
      return std::string();
  }
}
