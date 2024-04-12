String8 String8::walkPath(String8* outRemains) const
{
 const char* cp;
 const char*const str = mString;
 const char* buf = str;

    cp = strchr(buf, OS_PATH_SEPARATOR);
 if (cp == buf) {
        buf = buf+1;
        cp = strchr(buf, OS_PATH_SEPARATOR);
 }

 if (cp == NULL) {
 String8 res = buf != str ? String8(buf) : *this;
 if (outRemains) *outRemains = String8("");
 return res;
 }

 String8 res(buf, cp-buf);
 if (outRemains) *outRemains = String8(cp+1);
 return res;
}
