status_t Parcel::readPointer(uintptr_t *pArg) const
{
 status_t ret;
 binder_uintptr_t ptr;
    ret = readAligned(&ptr);
 if (!ret)
 *pArg = ptr;
 return ret;
}
