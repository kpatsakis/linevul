DisplayItem& PaintController::MoveItemFromCurrentListToNewList(size_t index) {
  items_moved_into_new_list_.resize(
      current_paint_artifact_.GetDisplayItemList().size());
  items_moved_into_new_list_[index] = new_display_item_list_.size();
  return new_display_item_list_.AppendByMoving(
      current_paint_artifact_.GetDisplayItemList()[index]);
}
