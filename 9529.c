void AutofillDialogViews::OnWidgetBoundsChanged(views::Widget* widget,
                                                const gfx::Rect& new_bounds) {
  if (error_bubble_ && error_bubble_->GetWidget() == widget)
    return;

  if (sign_in_delegate_ && sign_in_web_view_->visible()) {
    sign_in_delegate_->UpdateLimitsAndEnableAutoResize(
        GetMinimumSignInViewSize(), GetMaximumSignInViewSize());
  }
  HideErrorBubble();
}
