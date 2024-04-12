bool InjectedBundlePage::shouldInsertText(WKStringRef text, WKBundleRangeHandleRef rangeToReplace, WKInsertActionType action)
{
    if (!InjectedBundle::shared().isTestRunning())
        return true;

    static const char *insertactionstring[] = {
        "WebViewInsertActionTyped",
        "WebViewInsertActionPasted",
        "WebViewInsertActionDropped",
    };

    if (InjectedBundle::shared().testRunner()->shouldDumpEditingCallbacks()) {
        StringBuilder stringBuilder;
        stringBuilder.appendLiteral("EDITING DELEGATE: shouldInsertText:");
        stringBuilder.append(toWTFString(text));
        stringBuilder.appendLiteral(" replacingDOMRange:");
        stringBuilder.append(rangeToStr(m_page, m_world.get(), rangeToReplace));
        stringBuilder.appendLiteral(" givenAction:");
        stringBuilder.append(insertactionstring[action]);
        stringBuilder.append('\n');
        InjectedBundle::shared().outputText(stringBuilder.toString());
    }
    return InjectedBundle::shared().testRunner()->shouldAllowEditing();
}
