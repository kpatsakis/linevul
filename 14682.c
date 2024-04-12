bool WebView::registerWebViewWindowClass()
{
    static bool haveRegisteredWindowClass = false;
    if (haveRegisteredWindowClass)
        return true;
    haveRegisteredWindowClass = true;

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_DBLCLKS;
    wcex.lpfnWndProc    = WebView::WebViewWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = sizeof(WebView*);
    wcex.hInstance      = instanceHandle();
    wcex.hIcon          = 0;
    wcex.hCursor        = ::LoadCursor(0, IDC_ARROW);
    wcex.hbrBackground  = 0;
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = kWebKit2WebViewWindowClassName;
    wcex.hIconSm        = 0;

    return !!::RegisterClassEx(&wcex);
}
