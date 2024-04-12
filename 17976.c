bool Browser::CallBeforeUnloadHandlers(
    const base::Callback<void(bool)>& on_close_confirmed) {
  cancel_download_confirmation_state_ = RESPONSE_RECEIVED;
  if (IsFastTabUnloadEnabled()) {
    return fast_unload_controller_->CallBeforeUnloadHandlers(
        on_close_confirmed);
  }
  return unload_controller_->CallBeforeUnloadHandlers(on_close_confirmed);
}
