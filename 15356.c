status_t GraphicBuffer::lockAsync(uint32_t usage, void** vaddr, int fenceFd)
{
 const Rect lockBounds(width, height);
 status_t res = lockAsync(usage, lockBounds, vaddr, fenceFd);
 return res;
}
