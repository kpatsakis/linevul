     ~GraphicsSurfacePrivate()
    {
        if (m_glxPixmap)
            glXDestroyPixmap(m_display, m_glxPixmap);
        m_glxPixmap = 0;

        if (m_xPixmap)
            XFreePixmap(m_display, m_xPixmap);
        m_xPixmap = 0;

        if (m_display)
            XCloseDisplay(m_display);
        m_display = 0;
    }
