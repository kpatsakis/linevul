bool BaseArena::LazySweepWithDeadline(double deadline_seconds) {
  static const int kDeadlineCheckInterval = 10;

  CHECK(GetThreadState()->IsSweepingInProgress());
  DCHECK(GetThreadState()->SweepForbidden());
  DCHECK(ScriptForbiddenScope::IsScriptForbidden());

  NormalPageArena* normal_arena = nullptr;
  if (first_unswept_page_ && !first_unswept_page_->IsLargeObjectPage()) {
    NormalPage* normal_page =
        reinterpret_cast<NormalPage*>(first_unswept_page_);
    normal_arena = normal_page->ArenaForNormalPage();
    normal_arena->SetIsLazySweeping(true);
  }
  int page_count = 1;
  while (!SweepingCompleted()) {
    SweepUnsweptPage();
    if (page_count % kDeadlineCheckInterval == 0) {
      if (deadline_seconds <= CurrentTimeTicksInSeconds()) {
        ThreadHeap::ReportMemoryUsageForTracing();
        if (normal_arena)
          normal_arena->SetIsLazySweeping(false);
        return SweepingCompleted();
      }
    }
    page_count++;
  }
  ThreadHeap::ReportMemoryUsageForTracing();
  if (normal_arena)
    normal_arena->SetIsLazySweeping(false);
  return true;
}
