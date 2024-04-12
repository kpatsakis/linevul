bool UrlData::ValidateDataOrigin(const GURL& origin) {
  if (!have_data_origin_) {
    data_origin_ = origin;
    have_data_origin_ = true;
    return true;
  }
  if (cors_mode_ == UrlData::CORS_UNSPECIFIED) {
    return data_origin_ == origin;
  }
  return true;
}
