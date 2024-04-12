status_t Parcel::write(const void* data, size_t len)
{
 void* const d = writeInplace(len);
 if (d) {
        memcpy(d, data, len);
 return NO_ERROR;
 }
 return mError;
}
