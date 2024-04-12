WKBundlePagePolicyAction InjectedBundlePage::decidePolicyForNewWindowAction(WKBundlePageRef, WKBundleFrameRef, WKBundleNavigationActionRef, WKURLRequestRef, WKStringRef, WKTypeRef*)
{
    return WKBundlePagePolicyActionUse;
}
