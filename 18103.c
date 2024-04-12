void PageInfoBubbleView::DidStartNavigation(content::NavigationHandle* handle) {
  GetWidget()->Close();
}
