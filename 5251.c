void Document::setCookie(const String& value, ExceptionState& exceptionState)
{
    if (settings() && !settings()->cookieEnabled())
        return;


    if (!getSecurityOrigin()->canAccessCookies()) {
        if (isSandboxed(SandboxOrigin))
            exceptionState.throwSecurityError("The document is sandboxed and lacks the 'allow-same-origin' flag.");
        else if (url().protocolIs("data"))
            exceptionState.throwSecurityError("Cookies are disabled inside 'data:' URLs.");
        else
            exceptionState.throwSecurityError("Access is denied for this document.");
        return;
    }

    if (getSecurityOrigin()->hasSuborigin() && !getSecurityOrigin()->suborigin()->policyContains(Suborigin::SuboriginPolicyOptions::UnsafeCookies))
        return;

    KURL cookieURL = this->cookieURL();
    if (cookieURL.isEmpty())
        return;

    setCookies(this, cookieURL, value);
}