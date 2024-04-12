void CCThreadProxy::initializeLayerRendererOnCCThread(GraphicsContext3D* contextPtr, CCCompletionEvent* completion, bool* initializeSucceeded, LayerRendererCapabilities* capabilities, int* compositorIdentifier)
{
    TRACE_EVENT("CCThreadProxy::initializeLayerRendererOnCCThread", this, 0);
    ASSERT(isImplThread());
    RefPtr<GraphicsContext3D> context(adoptRef(contextPtr));
    *initializeSucceeded = m_layerTreeHostImpl->initializeLayerRenderer(context);
    if (*initializeSucceeded)
        *capabilities = m_layerTreeHostImpl->layerRendererCapabilities();

    m_scrollControllerAdapterOnCCThread = CCThreadProxyScrollControllerAdapter::create(this);
    m_inputHandlerOnCCThread = CCInputHandler::create(m_scrollControllerAdapterOnCCThread.get());
    *compositorIdentifier = m_inputHandlerOnCCThread->identifier();

    completion->signal();
}
