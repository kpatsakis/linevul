static TriState StateOrderedList(LocalFrame& frame, Event*) {
  return SelectionListState(frame.Selection(), olTag);
}
