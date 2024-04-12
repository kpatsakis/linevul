void HTMLMediaElement::WaitForSourceChange() {
  BLINK_MEDIA_LOG << "waitForSourceChange(" << (void*)this << ")";

  StopPeriodicTimers();
  load_state_ = kWaitingForSource;

  SetNetworkState(kNetworkNoSource);

  SetShouldDelayLoadEvent(false);

  UpdateDisplayState();

  if (GetLayoutObject())
     GetLayoutObject()->UpdateFromElement();
 }
