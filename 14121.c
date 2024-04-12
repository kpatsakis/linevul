static void texImage2DResourceSafe(size_t width, size_t height)
{
    const int pixelSize = 4; // RGBA
    OwnArrayPtr<unsigned char> zero;
    if (width && height) {
        unsigned int size = width * height * pixelSize;
        zero = adoptArrayPtr(new unsigned char[size]);
        memset(zero.get(), 0, size);
    }
    GL_CMD(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, zero.get()))
}
