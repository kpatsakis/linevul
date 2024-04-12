void ThreadHeap::ResetHeapCounters() {
  DCHECK(thread_state_->InAtomicMarkingPause());

  ThreadHeap::ReportMemoryUsageForTracing();

  ProcessHeap::DecreaseTotalAllocatedObjectSize(stats_.AllocatedObjectSize());
  ProcessHeap::DecreaseTotalMarkedObjectSize(stats_.MarkedObjectSize());

  stats_.Reset();
}
