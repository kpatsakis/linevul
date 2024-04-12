void AutofillDialogViews::OnWidgetClosing(views::Widget* widget) {
  observer_.Remove(widget);
  if (error_bubble_ && error_bubble_->GetWidget() == widget)
    error_bubble_ = NULL;
}
