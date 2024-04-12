status_t GraphicBuffer::lockYCbCr(uint32_t usage, const Rect& rect,
        android_ycbcr *ycbcr)
{
 if (rect.left < 0 || rect.right  > this->width ||
        rect.top  < 0 || rect.bottom > this->height) {
        ALOGE("locking pixels (%d,%d,%d,%d) outside of buffer (w=%d, h=%d)",
                rect.left, rect.top, rect.right, rect.bottom,
 this->width, this->height);
 return BAD_VALUE;
 }
 status_t res = getBufferMapper().lockYCbCr(handle, usage, rect, ycbcr);
 return res;
}
