void TabStripModel::AddTabContents(TabContents* contents,
                                   int index,
                                   content::PageTransition transition,
                                   int add_types) {
  bool inherit_group = (add_types & ADD_INHERIT_GROUP) == ADD_INHERIT_GROUP;

  if (transition == content::PAGE_TRANSITION_LINK &&
      (add_types & ADD_FORCE_INDEX) == 0) {
    index = order_controller_->DetermineInsertionIndex(
        contents, transition, add_types & ADD_ACTIVE);
    inherit_group = true;
  } else {
    if (index < 0 || index > count())
      index = order_controller_->DetermineInsertionIndexForAppending();
  }

  if (transition == content::PAGE_TRANSITION_TYPED && index == count()) {
    inherit_group = true;
  }
  InsertTabContentsAt(
      index, contents, add_types | (inherit_group ? ADD_INHERIT_GROUP : 0));
  index = GetIndexOfTabContents(contents);

  if (inherit_group && transition == content::PAGE_TRANSITION_TYPED)
    contents_data_[index]->reset_group_on_select = true;

  if (WebContents* old_contents = GetActiveWebContents()) {
    if ((add_types & ADD_ACTIVE) == 0) {
      contents->web_contents()->GetView()->
          SizeContents(old_contents->GetView()->GetContainerSize());
      contents->web_contents()->WasHidden();
    }
  }
}
