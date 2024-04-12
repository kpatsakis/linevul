void GaiaCookieManagerService::ForceOnCookieChangedProcessing() {
  GURL google_url = GaiaUrls::GetInstance()->google_url();
  std::unique_ptr<net::CanonicalCookie> cookie(net::CanonicalCookie::Create(
      google_url, kGaiaCookieName, std::string(), "." + google_url.host(),
      std::string(), base::Time(), base::Time(), false, false,
      net::CookieSameSite::DEFAULT_MODE, false, net::COOKIE_PRIORITY_DEFAULT));
  OnCookieChanged(*cookie, net::CookieStore::ChangeCause::UNKNOWN_DELETION);
}
