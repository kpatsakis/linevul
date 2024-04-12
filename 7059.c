void DocumentThreadableLoader::handlePreflightResponse(const ResourceResponse& response)
{
    String accessControlErrorDescription;

    if (!passesAccessControlCheck(response, effectiveAllowCredentials(), getSecurityOrigin(), accessControlErrorDescription, m_requestContext)) {
        handlePreflightFailure(response.url().getString(), "Response to preflight request doesn't pass access control check: " + accessControlErrorDescription);
        return;
    }

    if (!passesPreflightStatusCheck(response, accessControlErrorDescription)) {
        handlePreflightFailure(response.url().getString(), accessControlErrorDescription);
        return;
    }

    OwnPtr<CrossOriginPreflightResultCacheItem> preflightResult = adoptPtr(new CrossOriginPreflightResultCacheItem(effectiveAllowCredentials()));
    if (!preflightResult->parse(response, accessControlErrorDescription)
        || !preflightResult->allowsCrossOriginMethod(m_actualRequest.httpMethod(), accessControlErrorDescription)
        || !preflightResult->allowsCrossOriginHeaders(m_actualRequest.httpHeaderFields(), accessControlErrorDescription)) {
        handlePreflightFailure(response.url().getString(), accessControlErrorDescription);
        return;
    }

    CrossOriginPreflightResultCache::shared().appendEntry(getSecurityOrigin()->toString(), m_actualRequest.url(), preflightResult.release());
}
