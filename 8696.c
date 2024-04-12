static bool decodeBuffer(const char* buffer, unsigned size, const String& textEncodingName, String* result)
{
    if (buffer) {
        WTF::TextEncoding encoding(textEncodingName);
        if (!encoding.isValid())
            encoding = WindowsLatin1Encoding();
        *result = encoding.decode(buffer, size);
        return true;
    }
    return false;
}
