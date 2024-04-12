void Document::DispatchUnloadEvents(DocumentLoadTiming* timing) {
  PluginScriptForbiddenScope forbid_plugin_destructor_scripting;
  if (parser_)
    parser_->StopParsing();

  if (load_event_progress_ == kLoadEventNotRun)
    return;

  if (load_event_progress_ <= kUnloadEventInProgress) {
    Element* current_focused_element = FocusedElement();
    if (auto* input = ToHTMLInputElementOrNull(current_focused_element))
      input->EndEditing();
    if (load_event_progress_ < kPageHideInProgress) {
      load_event_progress_ = kPageHideInProgress;
      if (LocalDOMWindow* window = domWindow()) {
        const TimeTicks pagehide_event_start = CurrentTimeTicks();
        window->DispatchEvent(
            *PageTransitionEvent::Create(event_type_names::kPagehide, false),
            this);
        const TimeTicks pagehide_event_end = CurrentTimeTicks();
        DEFINE_STATIC_LOCAL(
            CustomCountHistogram, pagehide_histogram,
            ("DocumentEventTiming.PageHideDuration", 0, 10000000, 50));
        pagehide_histogram.CountMicroseconds(pagehide_event_end -
                                             pagehide_event_start);
      }
      if (!frame_)
        return;

      bool page_visible = IsPageVisible();
      load_event_progress_ = kUnloadVisibilityChangeInProgress;
      if (page_visible) {
        const TimeTicks pagevisibility_hidden_event_start = CurrentTimeTicks();
        DispatchEvent(
            *Event::CreateBubble(event_type_names::kVisibilitychange));
        const TimeTicks pagevisibility_hidden_event_end = CurrentTimeTicks();
        DEFINE_STATIC_LOCAL(CustomCountHistogram, pagevisibility_histogram,
                            ("DocumentEventTiming.PageVibilityHiddenDuration",
                             0, 10000000, 50));
        pagevisibility_histogram.CountMicroseconds(
            pagevisibility_hidden_event_end -
            pagevisibility_hidden_event_start);
        DispatchEvent(
            *Event::CreateBubble(event_type_names::kWebkitvisibilitychange));
      }
      if (!frame_)
        return;

      frame_->Loader().SaveScrollAnchor();

      load_event_progress_ = kUnloadEventInProgress;
      Event& unload_event = *Event::Create(event_type_names::kUnload);
      if (timing && timing->UnloadEventStart().is_null() &&
          timing->UnloadEventEnd().is_null()) {
        DCHECK(!timing->NavigationStart().is_null());
        const TimeTicks unload_event_start = CurrentTimeTicks();
        timing->MarkUnloadEventStart(unload_event_start);
        frame_->DomWindow()->DispatchEvent(unload_event, this);
        const TimeTicks unload_event_end = CurrentTimeTicks();
        DEFINE_STATIC_LOCAL(
            CustomCountHistogram, unload_histogram,
            ("DocumentEventTiming.UnloadDuration", 0, 10000000, 50));
        unload_histogram.CountMicroseconds(unload_event_end -
                                           unload_event_start);
        timing->MarkUnloadEventEnd(unload_event_end);
      } else {
        frame_->DomWindow()->DispatchEvent(unload_event, frame_->GetDocument());
      }
    }
    load_event_progress_ = kUnloadEventHandled;
  }
}
