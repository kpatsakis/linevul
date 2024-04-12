void DownloadItemImpl::MarkAsComplete() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  DCHECK(AllDataSaved());
  destination_info_.end_time = base::Time::Now();
  TransitionTo(COMPLETE_INTERNAL);
  UpdateObservers();
}
