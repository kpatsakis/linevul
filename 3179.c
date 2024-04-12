void Document::pluginLoadingTimerFired(Timer<Document>*)
{
    updateLayout();
}
