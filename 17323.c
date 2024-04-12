string16 GetAppListShortcutName() {
  chrome::VersionInfo::Channel channel = chrome::VersionInfo::GetChannel();
  if (channel == chrome::VersionInfo::CHANNEL_CANARY)
    return l10n_util::GetStringUTF16(IDS_APP_LIST_SHORTCUT_NAME_CANARY);
  return l10n_util::GetStringUTF16(IDS_APP_LIST_SHORTCUT_NAME);
}
