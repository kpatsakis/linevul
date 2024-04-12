void ScrollbarThemeWin::paintButton(GraphicsContext* gc, ScrollbarThemeClient* scrollbar, const IntRect& rect, ScrollbarPart part)
{
    bool horz = scrollbar->orientation() == HorizontalScrollbar;

    int partId;
    if (part == BackButtonStartPart || part == ForwardButtonStartPart)
        partId = horz ? DFCS_SCROLLLEFT : DFCS_SCROLLUP;
    else
        partId = horz ? DFCS_SCROLLRIGHT : DFCS_SCROLLDOWN;

    WebKit::WebCanvas* canvas = gc->canvas();
    WebKit::Platform::current()->themeEngine()->paintScrollbarArrow(canvas, getThemeArrowState(scrollbar, part), partId | getClassicThemeState(scrollbar, part), WebKit::WebRect(rect));
}
