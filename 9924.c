void BaseAudioContext::HandleStoppableSourceNodes() {
  DCHECK(IsAudioThread());
  DCHECK(IsGraphOwner());

  if (finished_source_handlers_.size())
    ScheduleMainThreadCleanup();
}
