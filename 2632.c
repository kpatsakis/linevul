void FontCache::getTraitsInFamily(const AtomicString& familyName, Vector<unsigned>& traitsMasks)
{
    HWndDC hdc(0);

    LOGFONT logFont;
    logFont.lfCharSet = DEFAULT_CHARSET;
    unsigned familyLength = min(familyName.length(), static_cast<unsigned>(LF_FACESIZE - 1));
    familyName.string().copyTo(logFont.lfFaceName, 0, familyLength);
    logFont.lfFaceName[familyLength] = 0;
    logFont.lfPitchAndFamily = 0;

    TraitsInFamilyProcData procData(familyName);
    EnumFontFamiliesEx(hdc, &logFont, traitsInFamilyEnumProc, reinterpret_cast<LPARAM>(&procData), 0);
    copyToVector(procData.m_traitsMasks, traitsMasks);
}
