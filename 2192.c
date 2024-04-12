void Document::enforceInsecureRequestPolicy(WebInsecureRequestPolicy policy)
{
    setInsecureRequestPolicy(getInsecureRequestPolicy() | policy);
    if (frame())
        frame()->loader().client()->didEnforceInsecureRequestPolicy(getInsecureRequestPolicy());
}
