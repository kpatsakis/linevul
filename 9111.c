static void FillLogFont(const FontDescription& fontDescription, LOGFONT* winfont)
{
    winfont->lfHeight = -fontDescription.computedPixelSize();
    winfont->lfWidth = 0;
    winfont->lfEscapement = 0;
    winfont->lfOrientation = 0;
    winfont->lfUnderline = false;
    winfont->lfStrikeOut = false;
    winfont->lfCharSet = DEFAULT_CHARSET;
    winfont->lfOutPrecision = OUT_TT_ONLY_PRECIS;
    winfont->lfQuality = isRunningLayoutTest() ? NONANTIALIASED_QUALITY : DEFAULT_QUALITY; // Honor user's desktop settings.
    winfont->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    winfont->lfItalic = fontDescription.italic();
    winfont->lfWeight = toGDIFontWeight(fontDescription.weight());
}
