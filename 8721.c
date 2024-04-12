 views::View* LauncherView::GetAppListButtonView() const {
   for (int i = 0; i < model_->item_count(); ++i) {
     if (model_->items()[i].type == TYPE_APP_LIST)
      return view_model_->view_at(i);
  }

  NOTREACHED() << "Applist button not found";
  return NULL;
}
