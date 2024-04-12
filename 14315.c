int ScrollbarThemeWin::getThemeState(ScrollbarThemeClient* scrollbar, ScrollbarPart part) const
{
    if (scrollbar->pressedPart() == ThumbPart) {
        if (part == ThumbPart)
            return SCRBS_PRESSED;
        return (windowsVersion() < WindowsVista) ? SCRBS_NORMAL : SCRBS_HOVER;
    }
    if (!scrollbar->enabled())
        return SCRBS_DISABLED;
    if (scrollbar->hoveredPart() != part || part == BackTrackPart || part == ForwardTrackPart)
        return (scrollbar->hoveredPart() == NoPart || (windowsVersion() < WindowsVista)) ? SCRBS_NORMAL : SCRBS_HOVER;
    if (scrollbar->pressedPart() == NoPart)
        return SCRBS_HOT;
    return (scrollbar->pressedPart() == part) ? SCRBS_PRESSED : SCRBS_NORMAL;
}
