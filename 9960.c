void GetCookiesCallback(std::string* cookies_out,
                        base::RunLoop* run_loop,
                        const std::vector<net::CanonicalCookie>& cookies) {
  *cookies_out = net::CanonicalCookie::BuildCookieLine(cookies);
  run_loop->Quit();
}
