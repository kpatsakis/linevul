static void parseSourceList(CSPSourceList& sourceList, String& sources)
{
    Vector<UChar> characters;
    sources.appendTo(characters);
    sourceList.parse(characters.data(), characters.data() + characters.size());
}
