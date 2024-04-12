bool Extension::LoadThemeDisplayProperties(const DictionaryValue* theme_value,
                                           string16* error) {
  const DictionaryValue* display_properties_value = NULL;
  if (theme_value->GetDictionary(keys::kThemeDisplayProperties,
                                 &display_properties_value)) {
    theme_display_properties_.reset(
        display_properties_value->DeepCopy());
  }
  return true;
}
