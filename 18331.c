    void testEmptyPicture()
    {
        m_testSurface->initializeCurrentFrame();
        RefPtr<SkPicture> picture = m_testSurface->getPicture();
        EXPECT_TRUE((bool)picture.get());
        EXPECT_EQ(1, m_fakeImageBufferClient->frameCount());
        expectDisplayListEnabled(true);
    }
