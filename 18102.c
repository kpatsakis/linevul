void InjectedBundlePage::didReachApplicationCacheOriginQuota(WKBundlePageRef page, WKSecurityOriginRef origin, int64_t totalBytesNeeded, const void* clientInfo)
{
    static_cast<InjectedBundlePage*>(const_cast<void*>(clientInfo))->didReachApplicationCacheOriginQuota(origin, totalBytesNeeded);
}
