uint64_t GLES2Implementation::PrepareNextSwapId(
    SwapCompletedCallback completion_callback,
    PresentationCallback presentation_callback) {
  uint64_t swap_id = swap_id_++;
  pending_swap_callbacks_.emplace(swap_id, std::move(completion_callback));
  if (!presentation_callback.is_null()) {
    pending_presentation_callbacks_.emplace(swap_id,
                                            std::move(presentation_callback));
  }
  return swap_id;
}
