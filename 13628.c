void ExternalProtocolHandler::RecordHandleStateMetrics(bool checkbox_selected,
                                                       BlockState block_state) {
  HandleState handle_state = DONT_LAUNCH;
  switch (block_state) {
    case DONT_BLOCK:
      handle_state = checkbox_selected ? CHECKED_LAUNCH : LAUNCH;
      break;
    case BLOCK:
      handle_state =
          checkbox_selected ? CHECKED_DONT_LAUNCH_DEPRECATED : DONT_LAUNCH;
      break;
    case UNKNOWN:
      NOTREACHED();
      return;
  }
  DCHECK_NE(CHECKED_DONT_LAUNCH_DEPRECATED, handle_state);
  UMA_HISTOGRAM_ENUMERATION(kHandleStateMetric, handle_state,
                            HANDLE_STATE_LAST);
}
