    virtual void drawLayersOnCCThread(CCLayerTreeHostImpl*)
    {
        if (m_numDraws == 1)
          postSetNeedsCommitThenRedrawToMainThread();
        m_numDraws++;
        postSetNeedsRedrawToMainThread();
    }
