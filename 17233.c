static inline void addToHarfBuzzBufferInternal(hb_buffer_t* buffer,
    const FontDescription& fontDescription, const UChar* normalizedBuffer,
    unsigned startIndex, unsigned numCharacters)
{
    if (fontDescription.variant() == FontVariantSmallCaps
        && u_islower(normalizedBuffer[startIndex])) {
        String upperText = String(normalizedBuffer + startIndex, numCharacters)
            .upper();
        ASSERT(!upperText.is8Bit());
        hb_buffer_add_utf16(buffer, toUint16(upperText.characters16()),
            numCharacters, 0, numCharacters);
    } else {
        hb_buffer_add_utf16(buffer, toUint16(normalizedBuffer + startIndex),
            numCharacters, 0, numCharacters);
    }
}
