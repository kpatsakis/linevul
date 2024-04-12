void HTMLMediaElement::setPlaybackRate(double rate,
                                       ExceptionState& exception_state) {
  BLINK_MEDIA_LOG << "setPlaybackRate(" << (void*)this << ", " << rate << ")";

  if (rate != 0.0 && (rate < kMinRate || rate > kMaxRate)) {
    UseCounter::Count(GetDocument(),
                      WebFeature::kHTMLMediaElementMediaPlaybackRateOutOfRange);

    exception_state.ThrowDOMException(
        kNotSupportedError, "The provided playback rate (" +
                                String::Number(rate) + ") is not in the " +
                                "supported playback range.");

    return;
  }

  if (playback_rate_ != rate) {
    playback_rate_ = rate;
    ScheduleEvent(EventTypeNames::ratechange);
  }

  UpdatePlaybackRate();
}
