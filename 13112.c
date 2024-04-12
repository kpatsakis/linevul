String8 String8::getPathLeaf(void) const
{
 const char* cp;
 const char*const buf = mString;

    cp = strrchr(buf, OS_PATH_SEPARATOR);
 if (cp == NULL)
 return String8(*this);
 else
 return String8(cp+1);
}
