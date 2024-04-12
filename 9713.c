const char16_t* Parcel::readString16Inplace(size_t* outLen) const
{
 int32_t size = readInt32();
 if (size >= 0 && size < INT32_MAX) {
 *outLen = size;
 const char16_t* str = (const char16_t*)readInplace((size+1)*sizeof(char16_t));
 if (str != NULL) {
 return str;
 }
 }
 *outLen = 0;
 return NULL;
}
