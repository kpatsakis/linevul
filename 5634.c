String8::~String8()
{
 SharedBuffer::bufferFromData(mString)->release();
}
