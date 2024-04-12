void ProfilingService::MaybeRequestQuit() {
  DCHECK(ref_factory_);
  if (ref_factory_->HasNoRefs())
    context()->RequestQuit();
}
