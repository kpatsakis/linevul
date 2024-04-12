void TabStrip::SetDropArrow(
    const base::Optional<BrowserRootView::DropIndex>& index) {
  if (!index) {
    controller_->OnDropIndexUpdate(-1, false);
    drop_arrow_.reset();
    return;
  }

  controller_->OnDropIndexUpdate(index->value, index->drop_before);

  if (drop_arrow_ && (index == drop_arrow_->index))
    return;

  bool is_beneath;
  gfx::Rect drop_bounds =
      GetDropBounds(index->value, index->drop_before, &is_beneath);

  if (!drop_arrow_) {
    drop_arrow_ = std::make_unique<DropArrow>(*index, !is_beneath, GetWidget());
  } else {
    drop_arrow_->index = *index;
    if (is_beneath == drop_arrow_->point_down) {
      drop_arrow_->point_down = !is_beneath;
      drop_arrow_->arrow_view->SetImage(
          GetDropArrowImage(drop_arrow_->point_down));
    }
  }

  drop_arrow_->arrow_window->SetBounds(drop_bounds);
  drop_arrow_->arrow_window->Show();
}
