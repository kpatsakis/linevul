MediaStreamDevicesController::GetDevicePolicy(
    const char* policy_name,
    const char* whitelist_policy_name) const {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));


  PrefService* prefs = profile_->GetPrefs();

  if (IsInKioskMode()) {
    const base::ListValue* list = prefs->GetList(whitelist_policy_name);
    std::string value;
    for (size_t i = 0; i < list->GetSize(); ++i) {
      if (list->GetString(i, &value)) {
        ContentSettingsPattern pattern =
            ContentSettingsPattern::FromString(value);
        if (pattern == ContentSettingsPattern::Wildcard()) {
          DLOG(WARNING) << "Ignoring wildcard URL pattern: " << value;
          continue;
        }
        DLOG_IF(ERROR, !pattern.IsValid()) << "Invalid URL pattern: " << value;
        if (pattern.IsValid() && pattern.Matches(request_.security_origin))
          return ALWAYS_ALLOW;
      }
    }
  }

  if (!prefs->GetBoolean(policy_name))
    return ALWAYS_DENY;

  return POLICY_NOT_SET;
}
