void BitmapTextureGL::updateContents(PixelFormat pixelFormat, const IntRect& rect, void* bits)
{
    GL_CMD(glBindTexture(GL_TEXTURE_2D, m_id))
#ifdef TEXMAP_OPENGL_ES_2
    bool shouldSwizzle = false;
#endif

    GLint glFormat = GL_RGBA;
    switch (pixelFormat) {
    case RGBAFormat:
        glFormat = GL_RGBA;
        break;
    case RGBFormat:
        glFormat = GL_RGB;
        break;
    case BGRAFormat:
#ifdef TEXMAP_OPENGL_ES_2
        shouldSwizzle = true;
        glFormat = GL_RGBA;
#else
        glFormat = GL_BGRA;
#endif
        break;
    case BGRFormat:
#ifdef TEXMAP_OPENGL_ES_2
        shouldSwizzle = true;
        glFormat = GL_RGB;
#else
        glFormat = GL_BGR;
#endif
         break;
    }

#ifdef TEXMAP_OPENGL_ES_2
    if (shouldSwizzle)
        swizzleBGRAToRGBA(static_cast<uint32_t*>(bits), rect.size());
#endif
    GL_CMD(glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x(), rect.y(), rect.width(), rect.height(), glFormat, GL_UNSIGNED_BYTE, bits))
}
