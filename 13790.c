void GaiaCookieManagerService::AddAccountToCookie(
    const std::string& account_id,
    const std::string& source) {
  VLOG(1) << "GaiaCookieManagerService::AddAccountToCookie: " << account_id;
  access_token_ = std::string();
  AddAccountToCookieInternal(account_id, source);
}
