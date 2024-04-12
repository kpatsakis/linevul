std::string TranslateLegacyAvc1CodecIds(const std::string& codec_id) {
  uint32_t level_start = 0;
  std::string result;
  if (base::StartsWith(codec_id, "avc1.66.", base::CompareCase::SENSITIVE)) {
    level_start = 8;
    result = "avc1.4200";
  } else if (base::StartsWith(codec_id, "avc1.77.",
                              base::CompareCase::SENSITIVE)) {
    level_start = 8;
    result = "avc1.4D00";
  } else if (base::StartsWith(codec_id, "avc1.100.",
                              base::CompareCase::SENSITIVE)) {
    level_start = 9;
    result = "avc1.6400";
  }

  uint32_t level = 0;
  if (level_start > 0 &&
      base::StringToUint(codec_id.substr(level_start), &level) && level < 256) {
    result.push_back(IntToHex(level >> 4));
    result.push_back(IntToHex(level & 0xf));
    return result;
  }

  return codec_id;
}
