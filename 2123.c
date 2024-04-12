    virtual bool detach()
    {
        m_events.append(Detach);
        return TRUE;
    }
