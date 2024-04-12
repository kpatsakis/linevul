     void createPixmap(uint32_t winId)
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, winId, &attr);

        XRenderPictFormat* format = XRenderFindVisualFormat(m_display, attr.visual);
        m_hasAlpha = (format->type == PictTypeDirect && format->direct.alphaMask);
        m_size = IntSize(attr.width, attr.height);

        int numberOfConfigs;
        GLXFBConfig* configs = glXChooseFBConfig(m_display, XDefaultScreen(m_display), glxSpec, &numberOfConfigs);

        m_xPixmap = XCompositeNameWindowPixmap(m_display, winId);
        m_glxPixmap = glXCreatePixmap(m_display, *configs, m_xPixmap, glxAttributes);

        uint inverted = 0;
        glXQueryDrawable(m_display, m_glxPixmap, GLX_Y_INVERTED_EXT, &inverted);
        m_textureIsYInverted = !!inverted;

        XFree(configs);
    }
