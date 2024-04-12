String8& String8::convertToResPath()
{
#if OS_PATH_SEPARATOR != RES_PATH_SEPARATOR
 size_t len = length();
 if (len > 0) {
 char * buf = lockBuffer(len);
 for (char * end = buf + len; buf < end; ++buf) {
 if (*buf == OS_PATH_SEPARATOR)
 *buf = RES_PATH_SEPARATOR;
 }
        unlockBuffer(len);
 }
#endif
 return *this;
}
