void WebContext::setSessionCookieMode(SessionCookieMode mode) {
  DCHECK(!IsInitialized());
  construct_props_->session_cookie_mode =
      static_cast<content::CookieStoreConfig::SessionCookieMode>(mode);
}
