ElementShadow* ShadowRoot::owner() const
{
    if (host())
        return host()->shadow();
    return 0;
}
