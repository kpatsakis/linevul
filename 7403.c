DocumentLoader::DocumentLoader(const ResourceRequest& req, const SubstituteData& substituteData)
    : m_deferMainResourceDataLoad(true)
    , m_frame(0)
    , m_cachedResourceLoader(CachedResourceLoader::create(this))
    , m_writer(m_frame)
    , m_originalRequest(req)
    , m_substituteData(substituteData)
    , m_originalRequestCopy(req)
    , m_request(req)
    , m_originalSubstituteDataWasValid(substituteData.isValid())
    , m_committed(false)
    , m_isStopping(false)
    , m_gotFirstByte(false)
    , m_isClientRedirect(false)
    , m_isLoadingMultipartContent(false)
    , m_wasOnloadHandled(false)
    , m_stopRecordingResponses(false)
    , m_substituteResourceDeliveryTimer(this, &DocumentLoader::substituteResourceDeliveryTimerFired)
    , m_didCreateGlobalHistoryEntry(false)
    , m_loadingMainResource(false)
    , m_timeOfLastDataReceived(0.0)
    , m_identifierForLoadWithoutResourceLoader(0)
    , m_dataLoadTimer(this, &DocumentLoader::handleSubstituteDataLoadNow)
    , m_waitingForContentPolicy(false)
    , m_applicationCacheHost(adoptPtr(new ApplicationCacheHost(this)))
{
}
