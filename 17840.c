void Document::executeScriptsWaitingForResourcesIfNeeded()
{
    if (!haveStylesheetsAndImportsLoaded())
        return;
    if (ScriptableDocumentParser* parser = scriptableDocumentParser())
        parser->executeScriptsWaitingForResources();
}
