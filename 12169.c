void CCThreadProxy::setThread(CCThread* ccThread)
{
    s_ccThread = ccThread;
#ifndef NDEBUG
    CCProxy::setImplThread(s_ccThread->threadID());
#endif
}
