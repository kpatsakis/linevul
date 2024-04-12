uint32_t DefaultAudioDestinationHandler::GetCallbackBufferSize() const {
  DCHECK(IsMainThread());
  DCHECK(IsInitialized());

  return platform_destination_->CallbackBufferSize();
}
