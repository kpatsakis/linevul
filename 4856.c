void GLES2Implementation::OnSwapBufferPresented(
    uint64_t swap_id,
    const gfx::PresentationFeedback& feedback) {
  auto found = pending_presentation_callbacks_.find(swap_id);
  if (found == pending_presentation_callbacks_.end())
    return;
  std::move(found->second).Run(feedback);
  pending_presentation_callbacks_.erase(found);
}
