String8::String8(const char* o)
 : mString(allocFromUTF8(o, strlen(o)))
{
 if (mString == NULL) {
        mString = getEmptyString();
 }
}
