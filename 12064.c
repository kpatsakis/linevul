void XMLHttpRequest::createRequest(ExceptionState& es)
{
    if (m_url.protocolIs("blob") && m_method != "GET") {
        es.throwDOMException(NetworkError, ExceptionMessages::failedToExecute("send", "XMLHttpRequest", "'GET' is the only method allowed for 'blob:' URLs."));
        return;
    }

    bool uploadEvents = false;
    if (m_async) {
        m_progressEventThrottle.dispatchEvent(XMLHttpRequestProgressEvent::create(eventNames().loadstartEvent));
        if (m_requestEntityBody && m_upload) {
            uploadEvents = m_upload->hasEventListeners();
            m_upload->dispatchEvent(XMLHttpRequestProgressEvent::create(eventNames().loadstartEvent));
        }
    }

    m_sameOriginRequest = securityOrigin()->canRequest(m_url);

    m_uploadEventsAllowed = m_sameOriginRequest || uploadEvents || !isSimpleCrossOriginAccessRequest(m_method, m_requestHeaders);

    ResourceRequest request(m_url);
    request.setHTTPMethod(m_method);
    request.setTargetType(ResourceRequest::TargetIsXHR);

    InspectorInstrumentation::willLoadXHR(scriptExecutionContext(), this, m_method, m_url, m_async, m_requestEntityBody ? m_requestEntityBody->deepCopy() : 0, m_requestHeaders, m_includeCredentials);

    if (m_requestEntityBody) {
        ASSERT(m_method != "GET");
        ASSERT(m_method != "HEAD");
        request.setHTTPBody(m_requestEntityBody.release());
    }

    if (m_requestHeaders.size() > 0)
        request.addHTTPHeaderFields(m_requestHeaders);

    ThreadableLoaderOptions options;
    options.sendLoadCallbacks = SendCallbacks;
    options.sniffContent = DoNotSniffContent;
    options.preflightPolicy = uploadEvents ? ForcePreflight : ConsiderPreflight;
    options.allowCredentials = (m_sameOriginRequest || m_includeCredentials) ? AllowStoredCredentials : DoNotAllowStoredCredentials;
    options.credentialsRequested = m_includeCredentials ? ClientRequestedCredentials : ClientDidNotRequestCredentials;
    options.crossOriginRequestPolicy = UseAccessControl;
    options.securityOrigin = securityOrigin();
    options.initiator = FetchInitiatorTypeNames::xmlhttprequest;
    options.contentSecurityPolicyEnforcement = ContentSecurityPolicy::shouldBypassMainWorld(scriptExecutionContext()) ? DoNotEnforceContentSecurityPolicy : EnforceConnectSrcDirective;
    options.mixedContentBlockingTreatment = TreatAsActiveContent;
    options.timeoutMilliseconds = m_timeoutMilliseconds;

    m_exceptionCode = 0;
    m_error = false;

    if (m_async) {
        if (m_upload)
            request.setReportUploadProgress(true);

        ASSERT(!m_loader);
        m_loader = ThreadableLoader::create(scriptExecutionContext(), this, request, options);
        if (m_loader) {

            ASSERT(!hasPendingActivity());
            setPendingActivity(this);
        }
    } else {
        request.setPriority(ResourceLoadPriorityVeryHigh);
        InspectorInstrumentation::willLoadXHRSynchronously(scriptExecutionContext());
        ThreadableLoader::loadResourceSynchronously(scriptExecutionContext(), request, *this, options);
        InspectorInstrumentation::didLoadXHRSynchronously(scriptExecutionContext());
    }

    if (!m_exceptionCode && m_error)
        m_exceptionCode = NetworkError;
    if (m_exceptionCode)
        es.throwDOMException(m_exceptionCode);
}
