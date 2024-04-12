ScrollbarTheme& PaintLayerScrollableArea::GetPageScrollbarTheme() const {
  DCHECK(!HasBeenDisposed());

  Page* page = GetLayoutBox()->GetFrame()->GetPage();
  DCHECK(page);

  return page->GetScrollbarTheme();
}
