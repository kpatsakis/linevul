static void NPN_GetStringIdentifiers(const NPUTF8 **names, int32_t nameCount, NPIdentifier *identifiers)
{
    ASSERT(names);
    ASSERT(identifiers);

    if (!names || !identifiers)
        return;

    for (int32_t i = 0; i < nameCount; ++i)
        identifiers[i] = NPN_GetStringIdentifier(names[i]);
}
