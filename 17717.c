static int32_t NPN_IntFromIdentifier(NPIdentifier identifier)
{
    return static_cast<IdentifierRep*>(identifier)->number();
}
