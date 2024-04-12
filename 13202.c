void* Parcel::writeInplace(size_t len)
{
 if (len > INT32_MAX) {
 return NULL;
 }

 const size_t padded = pad_size(len);

 if (mDataPos+padded < mDataPos) {
 return NULL;
 }

 if ((mDataPos+padded) <= mDataCapacity) {
restart_write:
 uint8_t* const data = mData+mDataPos;

 if (padded != len) {
#if BYTE_ORDER == BIG_ENDIAN
 static const uint32_t mask[4] = {
 0x00000000, 0xffffff00, 0xffff0000, 0xff000000
 };
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
 static const uint32_t mask[4] = {
 0x00000000, 0x00ffffff, 0x0000ffff, 0x000000ff
 };
#endif
 *reinterpret_cast<uint32_t*>(data+padded-4) &= mask[padded-len];
 }

        finishWrite(padded);
 return data;
 }

 status_t err = growData(padded);
 if (err == NO_ERROR) goto restart_write;
 return NULL;
}
