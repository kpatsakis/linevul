void ConfirmInfoBar::Layout() {

  InfoBar::Layout();

  int available_width = AlertInfoBar::GetAvailableWidth();
  int ok_button_width = 0;
  int cancel_button_width = 0;
  gfx::Size ok_ps = ok_button_->GetPreferredSize();
  gfx::Size cancel_ps = cancel_button_->GetPreferredSize();

  if (GetDelegate()->GetButtons() & ConfirmInfoBarDelegate::BUTTON_OK) {
    ok_button_width = ok_ps.width();
  } else {
    ok_button_->SetVisible(false);
  }
  if (GetDelegate()->GetButtons() & ConfirmInfoBarDelegate::BUTTON_CANCEL) {
    cancel_button_width = cancel_ps.width();
  } else {
    cancel_button_->SetVisible(false);
  }

  cancel_button_->SetBounds(available_width - cancel_button_width,
                            OffsetY(this, cancel_ps), cancel_ps.width(),
                            cancel_ps.height());
  int spacing = cancel_button_width > 0 ? kButtonButtonSpacing : 0;
  ok_button_->SetBounds(cancel_button_->x() - spacing - ok_button_width,
                        OffsetY(this, ok_ps), ok_ps.width(), ok_ps.height());

  AlertInfoBar::Layout();

  link_->SetVisible(!link_->GetText().empty());
  gfx::Size link_ps = link_->GetPreferredSize();
  int link_x = label()->bounds().right() + kEndOfLabelSpacing;
  int link_w = std::min(GetAvailableWidth() - link_x, link_ps.width());
  link_->SetBounds(link_x, OffsetY(this, link_ps), link_w, link_ps.height());
}
