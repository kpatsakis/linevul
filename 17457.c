void InterstitialPageImpl::InterstitialPageRVHDelegateView::ShowPopupMenu(
    RenderFrameHost* render_frame_host,
    const gfx::Rect& bounds,
    int item_height,
    double item_font_size,
    int selected_item,
    const std::vector<MenuItem>& items,
    bool right_aligned,
    bool allow_multiple_selection) {
  NOTREACHED() << "InterstitialPage does not support showing popup menus.";
}
