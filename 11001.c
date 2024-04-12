void SettingLevelBubble::OnHideTimeout() {
  if (view_) {
    SettingLevelBubbleDelegateView* delegate =
        static_cast<SettingLevelBubbleDelegateView*>
        (view_->GetWidget()->widget_delegate());
    delegate->StartFade(false);
  }
}
