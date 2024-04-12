void FolderHeaderView::ButtonPressed(views::Button* sender,
                                     const ui::Event& event) {
  delegate_->GiveBackFocusToSearchBox();
  delegate_->NavigateBack(folder_item_, event);
}
