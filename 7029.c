void PaintController::ResetCurrentListIndices() {
  next_item_to_match_ = 0;
  next_item_to_index_ = 0;
  next_chunk_to_match_ = 0;
  under_invalidation_checking_begin_ = 0;
  under_invalidation_checking_end_ = 0;
  skipped_probable_under_invalidation_count_ = 0;
}
