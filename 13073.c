void Document::didLoadAllScriptBlockingResources()
{
    loadingTaskRunner()->postTask(BLINK_FROM_HERE, m_executeScriptsWaitingForResourcesTask->cancelAndCreate());

    if (frame())
        frame()->loader().client()->didRemoveAllPendingStylesheet();

    if (m_gotoAnchorNeededAfterStylesheetsLoad && view())
        view()->processUrlFragment(m_url);
}
