bool Extension::LoadManagedModeSites(
    const DictionaryValue* content_pack_value,
    string16* error) {
  if (!content_pack_value->HasKey(keys::kContentPackSites))
    return true;

  FilePath::StringType site_list_str;
  if (!content_pack_value->GetString(keys::kContentPackSites, &site_list_str)) {
    *error = ASCIIToUTF16(errors::kInvalidContentPackSites);
    return false;
  }

  content_pack_site_list_ = FilePath(site_list_str);

  return true;
}
