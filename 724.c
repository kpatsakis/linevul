DOMWindow::DOMWindow(Frame& frame)
    : frame_(frame),
      window_proxy_manager_(frame.GetWindowProxyManager()),
      window_is_closing_(false) {}
