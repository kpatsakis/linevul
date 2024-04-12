void AppListControllerDelegateImpl::LaunchApp(
    Profile* profile,
    const extensions::Extension* extension,
    AppListSource source,
    int event_flags) {
  AppListServiceImpl::RecordAppListAppLaunch();

  AppLaunchParams params(profile, extension, NEW_FOREGROUND_TAB,
                         extensions::SOURCE_APP_LAUNCHER);

  if (source != LAUNCH_FROM_UNKNOWN &&
      extension->id() == extensions::kWebStoreAppId) {
    GURL extension_url = extensions::AppLaunchInfo::GetFullLaunchURL(extension);
    params.override_url = net::AppendQueryParameter(
        extension_url,
        extension_urls::kWebstoreSourceField,
        AppListSourceToString(source));
  }

  FillLaunchParams(&params);
  OpenApplication(params);
}
