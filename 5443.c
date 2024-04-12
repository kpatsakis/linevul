void XMLHttpRequest::open(const String& method, const KURL& url, bool async, ExceptionState& es)
{
    internalAbort();
    State previousState = m_state;
    m_state = UNSENT;
    m_error = false;
    m_uploadComplete = false;

    clearResponse();
    clearRequest();

    ASSERT(m_state == UNSENT);

    if (!isValidHTTPToken(method)) {
        es.throwDOMException(SyntaxError, ExceptionMessages::failedToExecute("open", "XMLHttpRequest", "'" + method + "' is not a valid HTTP method."));
        return;
    }

    if (!isAllowedHTTPMethod(method)) {
        es.throwSecurityError(ExceptionMessages::failedToExecute("open", "XMLHttpRequest", "'" + method + "' HTTP method is unsupported."));
        return;
    }

    if (!ContentSecurityPolicy::shouldBypassMainWorld(scriptExecutionContext()) && !scriptExecutionContext()->contentSecurityPolicy()->allowConnectToSource(url)) {
        es.throwSecurityError("Refused to connect to '" + url.elidedString() + "' because it violates the document's Content Security Policy.");
        return;
    }

    if (!async && scriptExecutionContext()->isDocument()) {
        if (document()->settings() && !document()->settings()->syncXHRInDocumentsEnabled()) {
            es.throwDOMException(InvalidAccessError, ExceptionMessages::failedToExecute("open", "XMLHttpRequest", "synchronous requests are disabled for this page."));
            return;
        }

        if (url.protocolIsInHTTPFamily() && m_responseTypeCode != ResponseTypeDefault) {
            es.throwDOMException(InvalidAccessError, ExceptionMessages::failedToExecute("open", "XMLHttpRequest", "synchronous HTTP requests from a document must not set a response type."));
            return;
        }

        if (m_timeoutMilliseconds > 0) {
            es.throwDOMException(InvalidAccessError, ExceptionMessages::failedToExecute("open", "XMLHttpRequest", "synchronous requests must not set a timeout."));
            return;
        }
    }

    m_method = uppercaseKnownHTTPMethod(method);

    m_url = url;

    m_async = async;

    ASSERT(!m_loader);

    if (previousState != OPENED)
        changeState(OPENED);
    else
        m_state = OPENED;
}
