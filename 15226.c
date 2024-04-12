bool Document::needsLayoutTreeUpdate() const
{
    if (!isActive() || !view())
        return false;
    if (needsFullLayoutTreeUpdate())
        return true;
    if (childNeedsStyleRecalc())
        return true;
    if (childNeedsStyleInvalidation())
        return true;
    if (layoutView()->wasNotifiedOfSubtreeChange())
        return true;
    return false;
}
