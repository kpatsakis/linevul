bool IsNetworkStateError(blink::WebMediaPlayer::NetworkState state) {
  bool result = state == blink::WebMediaPlayer::kNetworkStateFormatError ||
                state == blink::WebMediaPlayer::kNetworkStateNetworkError ||
                state == blink::WebMediaPlayer::kNetworkStateDecodeError;
  DCHECK_EQ(state > blink::WebMediaPlayer::kNetworkStateLoaded, result);
  return result;
}
