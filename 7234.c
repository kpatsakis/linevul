void WebPageProxy::didChooseFilesForOpenPanel(const Vector<String>& fileURLs)
{
    if (!isValid())
        return;

#if ENABLE(WEB_PROCESS_SANDBOX)
    for (size_t i = 0; i < fileURLs.size(); ++i) {
        SandboxExtension::Handle sandboxExtensionHandle;
        SandboxExtension::createHandle(fileURLs[i], SandboxExtension::ReadOnly, sandboxExtensionHandle);
        process()->send(Messages::WebPage::ExtendSandboxForFileFromOpenPanel(sandboxExtensionHandle), m_pageID);
    }
#endif

    process()->send(Messages::WebPage::DidChooseFilesForOpenPanel(fileURLs), m_pageID);

    m_openPanelResultListener->invalidate();
    m_openPanelResultListener = 0;
}
