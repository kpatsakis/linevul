void Document::platformColorsChanged()
{
    if (!isActive())
        return;

    styleEngine().platformColorsChanged();
}
