static inline bool isValidCachedResult(const Font* font, hb_direction_t dir,
    const String& localeString, const CachedShapingResults* cachedResults)
{
    ASSERT(cachedResults);
    return cachedResults->dir == dir
        && cachedResults->font == *font
        && !cachedResults->font.loadingCustomFonts()
        && !font->loadingCustomFonts()
        && cachedResults->locale == localeString;
}
