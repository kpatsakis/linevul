void HTMLScriptRunner::execute(PassRefPtrWillBeRawPtr<Element> scriptElement, const TextPosition& scriptStartPosition)
{
    ASSERT(scriptElement);

    bool hadPreloadScanner = m_host->hasPreloadScanner();

    runScript(scriptElement.get(), scriptStartPosition);

    if (hasParserBlockingScript()) {
        if (isExecutingScript())
            return; // Unwind to the outermost HTMLScriptRunner::execute before continuing parsing.
        if (!hadPreloadScanner && m_host->hasPreloadScanner())
            m_host->appendCurrentInputStreamToPreloadScannerAndScan();
        executeParsingBlockingScripts();
    }
}
