void ExtensionPrefs::ClearPageOrdinal(const std::string& extension_id) {
  UpdatePageOrdinalMap(GetPageOrdinal(extension_id), StringOrdinal());
  UpdateExtensionPref(extension_id, kPrefPageOrdinal, NULL);
}
