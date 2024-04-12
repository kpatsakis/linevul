void WebContentsImpl::OnAudioStateChanged(bool is_audible) {
  SendPageMessage(new PageMsg_AudioStateChanged(MSG_ROUTING_NONE, is_audible));

  NotifyNavigationStateChanged(INVALIDATE_TYPE_TAB);

  was_ever_audible_ = was_ever_audible_ || is_audible;

  if (delegate_)
    delegate_->OnAudioStateChanged(this, is_audible);
}
