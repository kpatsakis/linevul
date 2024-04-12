String8::String8(const char32_t* o, size_t len)
 : mString(allocFromUTF32(o, len))
{
}
