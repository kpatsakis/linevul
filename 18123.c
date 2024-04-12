void HTMLScriptRunner::executeScriptsWaitingForLoad(Resource* resource)
{
    ASSERT(!isExecutingScript());
    ASSERT(hasParserBlockingScript());
    ASSERT_UNUSED(resource, m_parserBlockingScript.resource() == resource);
    ASSERT(m_parserBlockingScript.isReady());
    executeParsingBlockingScripts();
}
