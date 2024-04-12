    virtual void drawLayers()
    {
        CCLayerTreeHostImpl::drawLayers();
        m_testHooks->drawLayersOnCCThread(this);
    }
