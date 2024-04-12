status_t Parcel::readAligned(T *pArg) const {
    COMPILE_TIME_ASSERT_FUNCTION_SCOPE(PAD_SIZE(sizeof(T)) == sizeof(T));

 if ((mDataPos+sizeof(T)) <= mDataSize) {
 const void* data = mData+mDataPos;
        mDataPos += sizeof(T);
 *pArg = *reinterpret_cast<const T*>(data);
 return NO_ERROR;
 } else {
 return NOT_ENOUGH_DATA;
 }
}
