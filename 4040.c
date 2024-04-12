void FolderHeaderView::OnPaint(gfx::Canvas* canvas) {
  views::View::OnPaint(canvas);

  gfx::Rect rect(GetContentsBounds());
  if (rect.IsEmpty() || !folder_name_visible_)
    return;

  rect.set_x((rect.width() - kBottomSeparatorWidth) / 2 + rect.x());
  rect.set_y(rect.y() + rect.height() - kBottomSeparatorHeight);
  rect.set_width(kBottomSeparatorWidth);
  rect.set_height(kBottomSeparatorHeight);
  canvas->FillRect(rect, kTopSeparatorColor);
}
