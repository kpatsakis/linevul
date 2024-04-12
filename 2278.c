bool Document::isInInvisibleSubframe() const
{
    if (!localOwner())
        return false; // this is a local root element

    DCHECK(frame());
    return !frame()->ownerLayoutObject();
}
