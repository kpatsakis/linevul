bool OSExchangeData::HasAnyFormat(
    int formats,
    const std::set<CustomFormat>& custom_formats) const {
  if ((formats & STRING) != 0 && HasString())
    return true;
  if ((formats & URL) != 0 && HasURL())
    return true;
#if defined(OS_WIN)
  if ((formats & FILE_CONTENTS) != 0 && provider_->HasFileContents())
    return true;
#endif
#if defined(OS_WIN) || defined(USE_AURA)
  if ((formats & HTML) != 0 && provider_->HasHtml())
    return true;
#endif
  if ((formats & FILE_NAME) != 0 && provider_->HasFile())
    return true;
  for (std::set<CustomFormat>::const_iterator i = custom_formats.begin();
       i != custom_formats.end(); ++i) {
    if (HasCustomFormat(*i))
      return true;
  }
  return false;
}
