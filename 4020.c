void HTMLDocumentParser::insert(const SegmentedString& source)
{
    if (isStopped())
        return;

    RefPtr<HTMLDocumentParser> protect(this);

    SegmentedString excludedLineNumberSource(source);
    excludedLineNumberSource.setExcludeLineNumbers();
    m_input.insertAtCurrentInsertionPoint(excludedLineNumberSource);
    pumpTokenizerIfPossible(ForceSynchronous);
    
    if (isWaitingForScripts()) {
        if (!m_insertionPreloadScanner)
            m_insertionPreloadScanner = adoptPtr(new HTMLPreloadScanner(document(), m_options));
        m_insertionPreloadScanner->appendToEnd(source);
        m_insertionPreloadScanner->scan();
    }

    endIfDelayed();
}
