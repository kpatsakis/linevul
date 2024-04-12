void EventConverterEvdevImpl::ProcessEvents(const input_event* inputs,
                                            int count) {
  for (int i = 0; i < count; ++i) {
    const input_event& input = inputs[i];
    switch (input.type) {
      case EV_KEY:
        ConvertKeyEvent(input);
        break;
      case EV_REL:
        ConvertMouseMoveEvent(input);
        break;
      case EV_SYN:
        if (input.code == SYN_DROPPED)
          OnLostSync();
        else if (input.code == SYN_REPORT)
          FlushEvents(input);
        break;
    }
  }
}
