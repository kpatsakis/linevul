status_t SampleTable::setChunkOffsetParams(
 uint32_t type, off64_t data_offset, size_t data_size) {
 if (mChunkOffsetOffset >= 0) {
 return ERROR_MALFORMED;
 }

    CHECK(type == kChunkOffsetType32 || type == kChunkOffsetType64);

    mChunkOffsetOffset = data_offset;
    mChunkOffsetType = type;

 if (data_size < 8) {
 return ERROR_MALFORMED;
 }

 uint8_t header[8];
 if (mDataSource->readAt(
                data_offset, header, sizeof(header)) < (ssize_t)sizeof(header)) {
 return ERROR_IO;
 }

 if (U32_AT(header) != 0) {
 return ERROR_MALFORMED;
 }

    mNumChunkOffsets = U32_AT(&header[4]);

 if (mChunkOffsetType == kChunkOffsetType32) {
 if ((data_size - 8) / 4 < mNumChunkOffsets) {
 return ERROR_MALFORMED;
 }
 } else {
 if ((data_size - 8) / 8 < mNumChunkOffsets) {
 return ERROR_MALFORMED;
 }
 }

 return OK;
}
