AutofillDialogViews::DetailsGroup* AutofillDialogViews::GroupForView(
    views::View* view) {
  DCHECK(view);

  views::View* input_view = GetAncestralInputView(view);
  if (!input_view)
    return NULL;

  for (DetailGroupMap::iterator iter = detail_groups_.begin();
       iter != detail_groups_.end(); ++iter) {
    DetailsGroup* group = &iter->second;
    if (input_view->parent() == group->manual_input)
      return group;

    if (input_view == group->suggested_info->textfield()) {
      return group;
    }
  }

  return NULL;
}
