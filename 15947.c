base::string16 passwords_empty_str(const std::string& domain) {
  return l10n_util::GetStringFUTF16(
      IDS_PASSWORD_MANAGER_ACCESSORY_PASSWORD_LIST_EMPTY_MESSAGE,
      ASCIIToUTF16(domain));
}
