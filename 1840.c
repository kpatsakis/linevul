void QuotaTask::Start() {
  DCHECK(observer_);
  observer()->RegisterTask(this);
  Run();
}
