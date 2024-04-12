void LocalDOMWindow::moveBy(int x, int y) const {
  if (!GetFrame() || !GetFrame()->IsMainFrame())
    return;

  Page* page = GetFrame()->GetPage();
  if (!page)
    return;

  IntRect window_rect = page->GetChromeClient().RootWindowRect();
  window_rect.SaturatedMove(x, y);
  page->GetChromeClient().SetWindowRectWithAdjustment(window_rect, *GetFrame());
}
