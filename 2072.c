void AppLauncherHandler::CreateAppInfo(
    const Extension* extension,
    ExtensionService* service,
    base::DictionaryValue* value) {
  value->Clear();

  base::string16 short_name = base::UTF8ToUTF16(extension->short_name());
  base::i18n::UnadjustStringForLocaleDirection(&short_name);
  NewTabUI::SetUrlTitleAndDirection(
      value,
      short_name,
      extensions::AppLaunchInfo::GetFullLaunchURL(extension));

  base::string16 name = base::UTF8ToUTF16(extension->name());
  base::i18n::UnadjustStringForLocaleDirection(&name);
  NewTabUI::SetFullNameAndDirection(name, value);

  bool enabled =
      service->IsExtensionEnabled(extension->id()) &&
      !extensions::ExtensionRegistry::Get(service->GetBrowserContext())
           ->GetExtensionById(extension->id(),
                              extensions::ExtensionRegistry::TERMINATED);
  extensions::GetExtensionBasicInfo(extension, enabled, value);

  value->SetBoolean("mayDisable", extensions::ExtensionSystem::Get(
      service->profile())->management_policy()->UserMayModifySettings(
      extension, NULL));

  bool icon_big_exists = true;
  GURL icon_big = extensions::ExtensionIconSource::GetIconURL(
      extension,
      extension_misc::EXTENSION_ICON_LARGE,
      ExtensionIconSet::MATCH_BIGGER,
      false,
      &icon_big_exists);
  value->SetString("icon_big", icon_big.spec());
  value->SetBoolean("icon_big_exists", icon_big_exists);
  bool icon_small_exists = true;
  GURL icon_small = extensions::ExtensionIconSource::GetIconURL(
      extension,
      extension_misc::EXTENSION_ICON_BITTY,
      ExtensionIconSet::MATCH_BIGGER,
      false,
      &icon_small_exists);
  value->SetString("icon_small", icon_small.spec());
  value->SetBoolean("icon_small_exists", icon_small_exists);
  value->SetInteger("launch_container",
                    extensions::AppLaunchInfo::GetLaunchContainer(extension));
  ExtensionPrefs* prefs = ExtensionPrefs::Get(service->profile());
  value->SetInteger("launch_type", extensions::GetLaunchType(prefs, extension));
  value->SetBoolean("is_component",
                    extension->location() == extensions::Manifest::COMPONENT);
  value->SetBoolean("is_webstore",
      extension->id() == extension_misc::kWebStoreAppId);

  AppSorting* sorting = prefs->app_sorting();
  syncer::StringOrdinal page_ordinal = sorting->GetPageOrdinal(extension->id());
  if (!page_ordinal.IsValid()) {
    page_ordinal = extension->id() == extension_misc::kWebStoreAppId ?
        sorting->CreateFirstAppPageOrdinal() :
        sorting->GetNaturalAppPageOrdinal();
    sorting->SetPageOrdinal(extension->id(), page_ordinal);
  }
  value->SetInteger("page_index",
      sorting->PageStringOrdinalAsInteger(page_ordinal));

  syncer::StringOrdinal app_launch_ordinal =
      sorting->GetAppLaunchOrdinal(extension->id());
  if (!app_launch_ordinal.IsValid()) {
    app_launch_ordinal = extension->id() == extension_misc::kWebStoreAppId ?
        sorting->CreateFirstAppLaunchOrdinal(page_ordinal) :
        sorting->CreateNextAppLaunchOrdinal(page_ordinal);
    sorting->SetAppLaunchOrdinal(extension->id(), app_launch_ordinal);
  }
  value->SetString("app_launch_ordinal", app_launch_ordinal.ToInternalValue());
}
