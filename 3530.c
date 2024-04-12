xsltUnregisterAllExtModuleElement(void)
{
    xmlMutexLock(xsltExtMutex);

    xmlHashFree(xsltElementsHash, (xmlHashDeallocator) xsltFreeExtElement);
    xsltElementsHash = NULL;

    xmlMutexUnlock(xsltExtMutex);
}
