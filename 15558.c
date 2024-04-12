bool HTMLMediaElement::HasPendingActivity() const {
  if (should_delay_load_event_)
    return true;

  if (!media_source_ && network_state_ == kNetworkLoading)
    return true;

  {
    base::AutoReset<bool> scope(&official_playback_position_needs_update_,
                                false);

    if (CouldPlayIfEnoughData())
      return true;
  }

  if (seeking_)
    return true;

  if (async_event_queue_->HasPendingEvents())
    return true;

  return false;
}
