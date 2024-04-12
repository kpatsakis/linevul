void Document::maybeHandleHttpRefresh(const String& content, HttpRefreshType httpRefreshType)
{
    if (m_isViewSource || !m_frame)
        return;

    double delay;
    String refreshURL;
    if (!parseHTTPRefresh(content, httpRefreshType == HttpRefreshFromMetaTag, delay, refreshURL))
        return;
    if (refreshURL.isEmpty())
        refreshURL = url().string();
    else
        refreshURL = completeURL(refreshURL).string();

    if (protocolIsJavaScript(refreshURL)) {
        String message = "Refused to refresh " + m_url.elidedString() + " to a javascript: URL";
        addConsoleMessage(SecurityMessageSource, ErrorMessageLevel, message);
        return;
    }

    if (httpRefreshType == HttpRefreshFromMetaTag && isSandboxed(SandboxAutomaticFeatures)) {
        String message = "Refused to execute the redirect specified via '<meta http-equiv='refresh' content='...'>'. The document is sandboxed, and the 'allow-scripts' keyword is not set.";
        addConsoleMessage(SecurityMessageSource, ErrorMessageLevel, message);
        return;
    }
    m_frame->navigationScheduler()->scheduleRedirect(delay, refreshURL);
}
