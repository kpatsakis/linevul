static int32_t readSize(off64_t offset,
 const sp<DataSource> DataSource, uint8_t *numOfBytes) {
 uint32_t size = 0;
 uint8_t data;
 bool moreData = true;
 *numOfBytes = 0;

 while (moreData) {
 if (DataSource->readAt(offset, &data, 1) < 1) {
 return -1;
 }
        offset ++;
        moreData = (data >= 128) ? true : false;
        size = (size << 7) | (data & 0x7f); // Take last 7 bits
 (*numOfBytes) ++;
 }

 return size;
}
