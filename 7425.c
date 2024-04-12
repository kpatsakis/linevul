void VariationsSeedStore::RegisterPrefs(PrefRegistrySimple* registry) {
  registry->RegisterStringPref(prefs::kVariationsCompressedSeed, std::string());
  registry->RegisterStringPref(prefs::kVariationsSeed, std::string());
  registry->RegisterInt64Pref(prefs::kVariationsSeedDate,
                              base::Time().ToInternalValue());
  registry->RegisterStringPref(prefs::kVariationsSeedSignature, std::string());
  registry->RegisterStringPref(prefs::kVariationsCountry, std::string());
}
