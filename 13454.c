void RenderViewImpl::ApplyAutoResizeLimitsForWidget(const gfx::Size& min_size,
                                                    const gfx::Size& max_size) {
  webview()->EnableAutoResizeMode(min_size, max_size);
}
