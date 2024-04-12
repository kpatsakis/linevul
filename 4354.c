WKURLRequestRef InjectedBundlePage::willSendRequestForFrame(WKBundlePageRef, WKBundleFrameRef frame, uint64_t identifier, WKURLRequestRef request, WKURLResponseRef response)
{
    if (InjectedBundle::shared().isTestRunning()
        && InjectedBundle::shared().testRunner()->shouldDumpResourceLoadCallbacks()) {
        StringBuilder stringBuilder;
        dumpResourceURL(identifier, stringBuilder);
        stringBuilder.appendLiteral(" - willSendRequest ");
        dumpRequestDescriptionSuitableForTestResult(request, stringBuilder);
        stringBuilder.appendLiteral(" redirectResponse ");
        dumpResponseDescriptionSuitableForTestResult(response, stringBuilder);
        stringBuilder.append('\n');
        InjectedBundle::shared().outputText(stringBuilder.toString());
    }

    if (InjectedBundle::shared().isTestRunning() && InjectedBundle::shared().testRunner()->willSendRequestReturnsNull())
        return 0;

    WKRetainPtr<WKURLRef> redirectURL = adoptWK(WKURLResponseCopyURL(response));
    if (InjectedBundle::shared().isTestRunning() && InjectedBundle::shared().testRunner()->willSendRequestReturnsNullOnRedirect() && redirectURL) {
        InjectedBundle::shared().outputText("Returning null for this redirect\n");
        return 0;
    }

    WKRetainPtr<WKURLRef> url = adoptWK(WKURLRequestCopyURL(request));
    WKRetainPtr<WKStringRef> host = adoptWK(WKURLCopyHostName(url.get()));
    WKRetainPtr<WKStringRef> scheme = adoptWK(WKURLCopyScheme(url.get()));
    WKRetainPtr<WKStringRef> urlString = adoptWK(WKURLCopyString(url.get()));
    if (host && !WKStringIsEmpty(host.get())
        && isHTTPOrHTTPSScheme(scheme.get())
        && !WKStringIsEqualToUTF8CString(host.get(), "255.255.255.255") // Used in some tests that expect to get back an error.
        && !isLocalHost(host.get())) {
        bool mainFrameIsExternal = false;
        if (InjectedBundle::shared().isTestRunning()) {
            WKBundleFrameRef mainFrame = InjectedBundle::shared().topLoadingFrame();
            WKRetainPtr<WKURLRef> mainFrameURL = adoptWK(WKBundleFrameCopyURL(mainFrame));
            if (!mainFrameURL || WKStringIsEqualToUTF8CString(adoptWK(WKURLCopyString(mainFrameURL.get())).get(), "about:blank"))
                mainFrameURL = adoptWK(WKBundleFrameCopyProvisionalURL(mainFrame));

            WKRetainPtr<WKStringRef> mainFrameHost = WKURLCopyHostName(mainFrameURL.get());
            WKRetainPtr<WKStringRef> mainFrameScheme = WKURLCopyScheme(mainFrameURL.get());
            mainFrameIsExternal = isHTTPOrHTTPSScheme(mainFrameScheme.get()) && !isLocalHost(mainFrameHost.get());
        }
        if (!mainFrameIsExternal) {
            StringBuilder stringBuilder;
            stringBuilder.appendLiteral("Blocked access to external URL ");
            stringBuilder.append(toWTFString(urlString));
            stringBuilder.append('\n');
            InjectedBundle::shared().outputText(stringBuilder.toString());
            return 0;
        }
    }

    WKRetain(request);
    return request;
}
