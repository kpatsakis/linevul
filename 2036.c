void HTMLMediaElement::SetNetworkState(NetworkState state) {
  if (network_state_ == state)
    return;

  network_state_ = state;
  if (GetMediaControls())
    GetMediaControls()->NetworkStateChanged();
}
