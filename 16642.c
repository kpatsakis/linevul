bool IsDolbyVisionHEVCCodecId(const std::string& codec_id) {
  return base::StartsWith(codec_id, "dvh1.", base::CompareCase::SENSITIVE) ||
         base::StartsWith(codec_id, "dvhe.", base::CompareCase::SENSITIVE);
}
