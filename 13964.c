Element* Document::elementFromPoint(int x, int y) const
{
    if (!renderer())
        return 0;

    return TreeScope::elementFromPoint(x, y);
}
