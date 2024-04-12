    virtual void drawLayersOnCCThread(CCLayerTreeHostImpl* impl)
    {
        m_numDraws++;
        if (!impl->sourceFrameNumber())
            endTest();
    }
