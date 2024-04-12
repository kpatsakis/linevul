static void replaceCharsetInMediaType(String& mediaType, const String& charsetValue)
{
    unsigned int pos = 0, len = 0;

    findCharsetInMediaType(mediaType, pos, len);

    if (!len) {
        return;
    }

    while (len) {
        mediaType.replace(pos, len, charsetValue);
        unsigned int start = pos + charsetValue.length();
        findCharsetInMediaType(mediaType, pos, len, start);
    }
}
