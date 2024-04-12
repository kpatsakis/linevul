TaskQueueManager::AsValueWithSelectorResult(bool should_run,
                                            size_t selected_queue) const {
  DCHECK(main_thread_checker_.CalledOnValidThread());
  scoped_refptr<base::trace_event::TracedValue> state =
      new base::trace_event::TracedValue();
  state->BeginArray("queues");
  for (auto& queue : queues_)
    queue->AsValueInto(state.get());
  state->EndArray();
  state->BeginDictionary("selector");
  selector_->AsValueInto(state.get());
  state->EndDictionary();
  if (should_run)
    state->SetInteger("selected_queue", selected_queue);
  return state;
}
