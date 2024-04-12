void PageInfoBubbleView::OnWidgetDestroying(views::Widget* widget) {
  g_shown_bubble_type = BUBBLE_NONE;
  g_page_info_bubble = nullptr;
  presenter_->OnUIClosing();
}
