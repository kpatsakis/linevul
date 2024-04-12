void DataPipeProducerDispatcher::CancelTransit() {
  base::AutoLock lock(lock_);
  DCHECK(in_transit_);
  in_transit_ = false;

  HandleSignalsState state = GetHandleSignalsStateNoLock();
  watchers_.NotifyState(state);
}
