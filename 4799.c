void RendererSchedulerImpl::CreateTraceEventObjectSnapshotLocked() const {
  TRACE_EVENT_OBJECT_SNAPSHOT_WITH_ID(
      TRACE_DISABLED_BY_DEFAULT("renderer.scheduler.debug"),
      "RendererScheduler", this, AsValueLocked(helper_.NowTicks()));
}
