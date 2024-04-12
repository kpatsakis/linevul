base::string16 GetProfileIdFromPath(const base::FilePath& profile_path) {
  if (profile_path.empty())
    return base::string16();

  base::FilePath default_user_data_dir;
  if (chrome::GetDefaultUserDataDirectory(&default_user_data_dir) &&
      profile_path.DirName() == default_user_data_dir &&
      profile_path.BaseName().value() ==
          base::ASCIIToUTF16(chrome::kInitialProfile)) {
    return base::string16();
  }

  base::string16 basenames = profile_path.DirName().BaseName().value() +
      L"." + profile_path.BaseName().value();

  base::string16 profile_id;
  profile_id.reserve(basenames.size());

  for (size_t i = 0; i < basenames.length(); ++i) {
    if (base::IsAsciiAlpha(basenames[i]) ||
        base::IsAsciiDigit(basenames[i]) ||
        basenames[i] == L'.')
      profile_id += basenames[i];
  }

  return profile_id;
}
