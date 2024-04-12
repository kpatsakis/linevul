static NPIdentifier NPN_GetIntIdentifier(int32_t intid)
{
    return static_cast<NPIdentifier>(IdentifierRep::get(intid));
}
