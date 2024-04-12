void Document::setCookie(const String& value, ExceptionCode& ec)
{
    if (page() && !page()->settings()->cookieEnabled())
        return;


    if (!securityOrigin()->canAccessCookies()) {
        ec = SECURITY_ERR;
        return;
    }

    KURL cookieURL = this->cookieURL();
    if (cookieURL.isEmpty())
        return;

    setCookies(this, cookieURL, value);
}
