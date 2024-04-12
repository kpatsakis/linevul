bool VariationsSeedStore::ReadSeedData(std::string* seed_data) {
  std::string base64_seed_data =
      local_state_->GetString(prefs::kVariationsCompressedSeed);
  const bool is_compressed = !base64_seed_data.empty();
  if (!is_compressed)
    base64_seed_data = local_state_->GetString(prefs::kVariationsSeed);

  if (base64_seed_data.empty()) {
    RecordVariationSeedEmptyHistogram(VARIATIONS_SEED_EMPTY);
    return false;
  }

  std::string decoded_data;
  if (!base::Base64Decode(base64_seed_data, &decoded_data)) {
    ClearPrefs();
    RecordVariationSeedEmptyHistogram(VARIATIONS_SEED_CORRUPT_BASE64);
    return false;
  }

  if (!is_compressed) {
    seed_data->swap(decoded_data);
  } else if (!metrics::GzipUncompress(decoded_data, seed_data)) {
    ClearPrefs();
    RecordVariationSeedEmptyHistogram(VARIATIONS_SEED_CORRUPT_GZIP);
    return false;
  }

  return true;
}
