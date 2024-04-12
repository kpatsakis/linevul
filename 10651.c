String8::String8(const String8& o)
 : mString(o.mString)
{
 SharedBuffer::bufferFromData(mString)->acquire();
}
