void ConfirmInfoBar::Layout() {
  InfoBarView::Layout();

  int x = StartX();
  Labels labels;
  labels.push_back(label_);
  labels.push_back(link_);
  AssignWidths(&labels, std::max(0, EndX() - x - NonLabelWidth()));

  ChromeLayoutProvider* layout_provider = ChromeLayoutProvider::Get();

  label_->SetPosition(gfx::Point(x, OffsetY(label_)));
  if (!label_->text().empty())
    x = label_->bounds().right() +
        layout_provider->GetDistanceMetric(
            views::DISTANCE_RELATED_LABEL_HORIZONTAL);

  if (ok_button_) {
    ok_button_->SetPosition(gfx::Point(x, OffsetY(ok_button_)));
    x = ok_button_->bounds().right() +
        layout_provider->GetDistanceMetric(
            views::DISTANCE_RELATED_BUTTON_HORIZONTAL);
  }

  if (cancel_button_)
    cancel_button_->SetPosition(gfx::Point(x, OffsetY(cancel_button_)));

  link_->SetPosition(gfx::Point(EndX() - link_->width(), OffsetY(link_)));
}
