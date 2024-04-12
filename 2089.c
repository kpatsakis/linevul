static bool isNonCanonicalCharacter(UChar c)
{
    return (c == '\\' || c == '0' || c == '\0' || c >= 127);
}
