void AutofillDialogViews::ShowErrorBubbleForViewIfNecessary(views::View* view) {
  if (!view->GetWidget())
    return;

  if (!delegate_->ShouldShowErrorBubble()) {
    DCHECK(!error_bubble_);
    return;
  }

  if (view->GetClassName() == DecoratedTextfield::kViewClassName &&
      !static_cast<DecoratedTextfield*>(view)->invalid()) {
    return;
  }

  views::View* input_view = GetAncestralInputView(view);
  std::map<views::View*, base::string16>::iterator error_message =
      validity_map_.find(input_view);
  if (error_message != validity_map_.end()) {
    input_view->ScrollRectToVisible(input_view->GetLocalBounds());

    if (!error_bubble_ || error_bubble_->anchor() != view) {
      HideErrorBubble();
      error_bubble_ = new InfoBubble(view, error_message->second);
      error_bubble_->set_align_to_anchor_edge(true);
      error_bubble_->set_preferred_width(
          (kSectionContainerWidth - views::kRelatedControlVerticalSpacing) / 2);
      bool show_above = view->GetClassName() == views::Combobox::kViewClassName;
      error_bubble_->set_show_above_anchor(show_above);
      error_bubble_->Show();
      observer_.Add(error_bubble_->GetWidget());
    }
  }
}
