String Document::cookie(ExceptionState& exception_state) const {
  if (GetSettings() && !GetSettings()->GetCookieEnabled())
    return String();

  UseCounter::Count(*this, WebFeature::kCookieGet);


  if (!GetSecurityOrigin()->CanAccessCookies()) {
    if (IsSandboxed(kSandboxOrigin))
      exception_state.ThrowSecurityError(
          "The document is sandboxed and lacks the 'allow-same-origin' flag.");
    else if (Url().ProtocolIs("data"))
      exception_state.ThrowSecurityError(
          "Cookies are disabled inside 'data:' URLs.");
    else
      exception_state.ThrowSecurityError("Access is denied for this document.");
    return String();
  }

  if (GetSecurityOrigin()->HasSuborigin() &&
      !GetSecurityOrigin()->GetSuborigin()->PolicyContains(
          Suborigin::SuboriginPolicyOptions::kUnsafeCookies))
    return String();

  KURL cookie_url = CookieURL();
  if (cookie_url.IsEmpty())
    return String();

  return Cookies(this, cookie_url);
}
