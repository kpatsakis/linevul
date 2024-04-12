    void didFailLoaderCreation()
    {
        m_callback->sendFailure("Couldn't create a loader");
        dispose();
    }
