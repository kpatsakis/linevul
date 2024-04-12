int ScrollbarThemeWin::scrollbarThickness(ScrollbarControlSize controlSize)
{
    static int thickness;
    if (!thickness) {
        if (isRunningLayoutTest())
            return kMacScrollbarSize[controlSize];
        thickness = IntSize(WebKit::Platform::current()->themeEngine()->getSize(SBP_ARROWBTN)).width();
    }
    return thickness;
}
