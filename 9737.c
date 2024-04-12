    ~AutoInstallCurrentThreadPlatformMock()
    {
        Platform::initialize(m_oldPlatform);
    }
